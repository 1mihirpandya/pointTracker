#include "ofApp.h"

//
// SETUP METHODS
//

/*
 * Sets up the application GUI and base functionality.
 */
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    width_ = default_width;
    height_ = default_height;
    video_.setup(width_,height_);
    setupTrackingFunctionality(width_, height_);
    setupDrawingFunctionality();
}

/*
 * Set up all the variables and values needed to track a color on the screen.
 */
void ofApp::setupTrackingFunctionality(int width, int height) {
    rgb_image_.allocate(width, height);
    hsb_image_.allocate(width, height);
    hue_image_.allocate(width, height);
    saturation_image_.allocate(width, height);
    brightness_image_.allocate(width, height);
    filtered_image_.allocate(width, height);
    missing_point_frame_counter_ = 0;
    target_hue_ = -1;
    set_shape_ = true;
    shape_area_ = {0, 0};
}

/*
 * Set up the user_objects_ and current_object_ to allow the user to draw.
 * Also sets up the color slider so users can pick their drawing color.
 */
void ofApp::setupDrawingFunctionality() {
    user_objects_.push_back(new ofPath());
    current_object_ = user_objects_.back();
    current_object_->setMode(ofPath::POLYLINES);
    current_object_->setFilled(false);
    current_object_->setStrokeWidth(line_width);
    current_object_->setColor(color_slider_);
    color_slider_.setup("Pick the line color you want!", ofColor(), ofColor(), 20, 300);
    color_slider_.setShape(0, 70, 250, 100);
    settings_active_ = false;
}

//
// DRAWING/LINE EDITING METHODS
//

/*
 * Draws the base image, the lines/shapes, the color slider (if applicable),
 * and the color picker.
 */
void ofApp::draw(){
    rgb_image_.draw(0,0);
    if (settings_active_){
        color_slider_.draw();
    }
    for (auto &line : user_objects_) {
        line->draw();
    }
    if (missing_point_frame_counter_ == 0)
    {
        missing_point_frame_counter_ += 1;
    } else {
        if (missing_point_frame_counter_ == max_missing_point_counter) {
            newObject();
            missing_point_frame_counter_ = max_missing_point_counter + 1;
        } else {
            missing_point_frame_counter_ += 1;
        }
    }
    ofPath color_picker;
    color_picker.setFilled(true);
    color_picker.setColor(target_color_);
    color_picker.rectangle(0, 0, color_picker_size, color_picker_size);
    color_picker.draw();
}

/*
 * Creates a new line (independent of all other lines drawn).
 */
void ofApp::newObject() {
    user_objects_.push_back(new ofPath());
    current_object_ = user_objects_.back();
}

/*
 * Makes a new shape based on the specification of the user.
 */
void ofApp::newShape(char shape_type) {
    newObject();
    if (shape_type == rectangle) {
        current_object_->rectangle(current_points_.at(0), current_points_.at(1), rectangle_width, rectangle_height);
    } else if (shape_type == circle) {
        current_object_->circle(current_points_.at(0), current_points_.at(1), circle_radius);
    } else if (shape_type == triangle) {
        int x = current_points_.at(0);
        int y = current_points_.at(1);
        current_object_->triangle(x, y, x - triangle_offset, y + triangle_offset, x + triangle_offset, y + triangle_offset);
    }
    shape_type_ = shape_type;
    current_object_->setFilled(true);
    current_object_->setColor(color_slider_);
    set_shape_ = false;
}

/*
 * Adds a point at the given index to the current line.
 */
void ofApp::addPoint(int x, int y) {
    ofPoint point;
    point.set(x,y);
    current_object_->lineTo(x, y);
    current_object_->setFilled(false);
    current_object_->setStrokeWidth(line_width);
    current_object_->setColor(color_slider_);
}

/*
 * Moves the shape in question or finalizes its location.
 */
void ofApp::setShape() {
    user_objects_.pop_back();
    delete current_object_;
    current_object_ = user_objects_.back();
    newShape(shape_type_);
    if (shape_area_.at(0) > 0 && std::abs(shape_area_.at(1) - shape_area_.at(0)) > depth_threshold) {
        set_shape_ = true;
        newObject();
    }
    missing_point_frame_counter_ = 0;
}

//
// POINT TRACKING METHODS
//

/*
 * Updates the video object. If the frame has changed, it will update the rgb_image_ variable
 * and go through the process of finding the closest approximation of the point to track.
 * This site was used as a reference when writing the color tracking portion: https://sites.google.com/site/ofauckland/examples/10-testing
 */
void ofApp::update(){
    video_.update();
    if (video_.isFrameNew()) {
        rgb_image_.setFromPixels(video_.getPixels());
        rgb_image_.resize(width_, height_);
        rgb_image_.mirror(false, true);
        if (target_hue_ > -1) {
            //find potential points via HSV and then apply the euclidian formula to further approximate the points
            findPotentialPoints();
            std::vector<int> approximate_points = applyEuclidianFormula();
            int approx_x = approximate_points.front();
            int approx_y = approximate_points.back();
            if (approx_x > -1 && approx_y > -1) {
                if (set_shape_) {
                    addPoint(approx_x, approx_y);
                    missing_point_frame_counter_ = 0;
                }
                current_points_ = approximate_points;
            }
            approximate_points.erase(approximate_points.begin(), approximate_points.end());
        }
        //if the application is in shape setting mode, call setShape();
        if (!set_shape_) {
            setShape();
        }
    }
}

/*
 * This method will filter out the pixels in the image using the hue. If the pixel hue
 * matches the desired hue, the pixel will be painted white. If not, the pixel will be made black.
 * This is to isolate all the possible points.
 */
void ofApp::findPotentialPoints() {
    hsb_image_ = rgb_image_;
    hsb_image_.convertRgbToHsv();
    hsb_image_.convertToGrayscalePlanarImages(hue_image_, saturation_image_, brightness_image_);
    for (int i = 0; i < width_ * height_; i++) {
        if (ofInRange(hue_image_.getPixels()[i],target_hue_ - hue_threshold, target_hue_ + hue_threshold)) {
            filtered_image_.getPixels()[i] = 255;
        } else {
            filtered_image_.getPixels()[i] = 0;
        }
    }
    filtered_image_.flagImageChanged();
    contours_.findContours(filtered_image_, min_contour_area, width_ * height_ / 2, 1, false);
}

/*
 * After finding the potential contour points, the euclidian formula will find
 * the coordinates of the countour "blob" with the color closest to the target_color_.
 */
std::vector<int> ofApp::applyEuclidianFormula() {
    float min_difference = 255;
    int approx_x = -1;
    int approx_y = -1;
    ofPixelsRef screen = video_.getPixels();
    for (int i = 0; i < contours_.nBlobs; i++) {
        ofColor color = screen.getColor(contours_.blobs[i].centroid.x, contours_.blobs[i].centroid.y);
        float r_difference = color.r - target_color_.r;
        float g_difference = color.g - target_color_.g;
        float b_difference = color.b - target_color_.b;
        float color_difference = sqrt(r_difference * r_difference + r_difference * r_difference + r_difference * r_difference);
        if(color_difference < min_difference){
            min_difference = color_difference;
            approx_x = contours_.blobs[i].centroid.x;
            approx_y = contours_.blobs[i].centroid.y;
            shape_area_.at(0) = shape_area_.at(1);
            shape_area_.at(1) = contours_.blobs[i].area;
        }
    }
    return {approx_x, approx_y};
}

//
// BUILD IN METHODS USED IN THE APPLICATION
//

/*
 * Allows users to safely delete all the lines (with d or D), clear the current line
 * (with b or B), activate the settings/line color picker (with s or S), or make a
 * new shape (r/R for rectange, c/C for circle, and t/T for triangle).
 */
void ofApp::keyPressed(int key){
    ofPoint point;
    if (key == 'd' || key == 'D'){
        for (int x = 0; x < user_objects_.size(); x++) {
            (user_objects_.at(x))->clear();
            user_objects_.erase(user_objects_.begin() + x);
            user_objects_.clear();
            newObject();
        }
    }
    else if (key == 'b' || key == 'B') {
        current_object_->clear();
    }
    else if (key == 's' || key == 'S') {
        settings_active_ = !settings_active_;
        if (!settings_active_) {
            current_object_->setColor(color_slider_);
        }
    } else if (key == 'r' || key == 'R') {
        newShape(rectangle);
    } else if (key == 'c' || key == 'C') {
        newShape(circle);
    } else if (key == 't' || key == 'T') {
        newShape(triangle);
    }
}

/*
 * Takes the clicked point's hue and color and set them as the new target_color_ and target_hue_.
 */
void ofApp::mousePressed(int x, int y, int button){
    //calculate the location of the "click"
    int scaled_x = x % width_;
    int scaled_y = y % height_;
    //get the rgb value of the mouse position and get hue_image_ value on mouse position
    target_hue_ = hue_image_.getPixels()[scaled_y * width_ + scaled_x];
    target_color_ = rgb_image_.getPixels().getColor(scaled_x, scaled_y);
}

/*
 * Updates the width and the height and updates all the image/video frames.
 */
void ofApp::windowResized(int w, int h){
    width_ = w;
    height_ = h;
    setupTrackingFunctionality(w, h);
}
