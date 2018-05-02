#include "ofApp.h"
#include <cmath>
#include <stdlib.h>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    point_onscreen_ = 0;
    width_ = 1320;	// try to grab at this size.
    height_ = 720;
    user_lines_.push_back(new ofPath());
    current_line_ = user_lines_.back();
    color_slider_.setup("Pick the line color you want!", ofColor(), ofColor(), 20, 300);
    color_slider_.setShape(0, 70, 250, 100);
    current_line_->setMode(ofPath::POLYLINES);
    current_line_->setFilled(false);
    current_line_->setStrokeWidth(5);
    current_line_->setColor(color_slider_);
    ofSetBackgroundAuto(false);
    video_.setup(width_,height_);
    ofEnableAlphaBlending();
    settings_active_ = false;
    rgb_image_.allocate(width_, height_);
    hsb_image_.allocate(width_, height_);
    hue_image_.allocate(width_, height_);
    saturation_image_.allocate(width_, height_);
    brightness_image_.allocate(width_, height_);
    filtered_image_.allocate(width_, height_);
    target_hue_ = -1;
    shape_set_ = true;
    shape_area_ = {0,0};
}


//--------------------------------------------------------------
//http://beriomolina.com/Tracking-colors-tracking-laser/
//https://sites.google.com/site/ofauckland/examples/10-testing
void ofApp::update(){
    video_.update();
    if (video_.isFrameNew()) {
        rgb_image_.setFromPixels(video_.getPixels());
        rgb_image_.resize(width_, height_);
        rgb_image_.mirror(false, true);
        if (target_hue_ > -1) {
            findPoint();
            std::vector<int> approximate_points = applyEuclidianFormula();
            int approx_x = approximate_points.front();
            int approx_y = approximate_points.back();
            if (approx_x > -1 && approx_y > -1) {
                if (shape_set_) {
        addPoint(approx_x, approx_y);
        point_onscreen_ = 0;
                }
                current_points_ = approximate_points;
            }
            approximate_points.erase(approximate_points.begin(), approximate_points.end());
        }
        if (!shape_set_) {
            user_lines_.pop_back();
            delete current_line_;
            current_line_ = user_lines_.back();
            newShape(shape_type_);
            if (shape_area_.at(0) > 0 && std::abs(shape_area_.at(1) - shape_area_.at(0)) > 300) {
                shape_set_ = true;
                newLine();
            }
            point_onscreen_ = 0;
        }
    }
}

std::vector<int> ofApp::applyEuclidianFormula() {
    float min_difference = 255;
    int approx_x = -1;
    int approx_y = -1;
    ofPixelsRef screen = video_.getPixels();
    for (int i=0; i<contours_.nBlobs; i++) {
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
            std::cout << shape_area_.at(0) << "  " << shape_area_.at(1) << std::endl;
        }
    }
    return {approx_x, approx_y};
}

void ofApp::findPoint() {
    hsb_image_ = rgb_image_;
    hsb_image_.convertRgbToHsv();
    hsb_image_.convertToGrayscalePlanarImages(hue_image_, saturation_image_, brightness_image_);
    
        for (int i = 0; i < width_ * height_; i++) {
            filtered_image_.getPixels()[i] = ofInRange(hue_image_.getPixels()[i],target_hue_-5,target_hue_+5) ? 255 : 0;
        }
        filtered_image_.flagImageChanged();
    contours_.findContours(filtered_image_, 50, width_ * height_/2, 1, false);
}


//--------------------------------------------------------------
void ofApp::draw(){
    rgb_image_.draw(0,0);
    if (settings_active_){
        color_slider_.draw();
    }
    for (auto &line : user_lines_) {
        line->draw();
    }
    if (point_onscreen_ == 0)
    {
        //current_line_->draw();
        point_onscreen_ += 1;
    } else {
        if (point_onscreen_ == 20) {
            newLine();
            point_onscreen_ = 21;
        } else {
            point_onscreen_ += 1;
        }
    }
    ofPath x;
    x.setFilled(true);
    x.setColor(target_color_);
    x.rectangle(0, 0, 64, 64);
    x.draw();
}

void ofApp::newLine() {
    user_lines_.push_back(new ofPath());
    current_line_ = user_lines_.back();
}

void ofApp::addPoint(int x, int y) {
    ofPoint point;
    point.set(x,y);
    current_line_->lineTo(x, y);
    current_line_->setFilled(false);
    current_line_->setStrokeWidth(5);
    current_line_->setColor(color_slider_);
}

void ofApp::newShape(char c) {
    newLine();
    if (c == 'r') {
    current_line_->rectangle(current_points_.at(0), current_points_.at(1), 100, 100);
        shape_type_ = 'r';
    } else if (c == 'c') {
        current_line_->circle(current_points_.at(0), current_points_.at(1), 50);
        shape_type_ = 'c';
    } else if (c == 't') {
        int x = current_points_.at(0);
        int y = current_points_.at(1);
        current_line_->triangle(x, y, x - 50, y + 50, x + 50, y + 50);
        shape_type_ = 't';
        //current_line_->rectangle(current_points_.at(0), current_points_.at(1), 100, 100);
    }
    current_line_->setFilled(true);
    current_line_->setColor(color_slider_);
    shape_set_ = false;
}
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //updates the point and adds the vertex to the line
    ofPoint point;
    if (key == 'd' || key == 'D'){
        for (int x = 0; x < user_lines_.size(); x++) {
            (user_lines_.at(x))->clear();
            user_lines_.erase(user_lines_.begin() + x);
            user_lines_.clear();
            newLine();
        }
    }
    else if (key == 'b' || key == 'B') {
        current_line_->clear();
    }
    else if (key == 's' || key == 'S') {
        settings_active_ = !settings_active_;
        if (!settings_active_) {
            current_line_->setColor(color_slider_);
        }
    } else if (key == 'r' || key == 'R') {
        newShape('r');
    } else if (key == 'c' || key == 'C') {
        newShape('c');
    } else if (key == 't' || key == 'T') {
        newShape('t');
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    std::cout << target_color_ << std::endl;
    //calculate local mouse x,y in image
    int mx = x % width_;
    int my = y % height_;
    //get hue_image_ value on mouse position
    target_hue_ = hue_image_.getPixels()[my * width_ + mx];
    target_color_ = rgb_image_.getPixels().getColor(mx, my);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    width_ = w;
    height_ = h;
    rgb_image_.allocate(width_, height_);
    hsb_image_.allocate(width_, height_);
    hue_image_.allocate(width_, height_);
    saturation_image_.allocate(width_, height_);
    brightness_image_.allocate(width_, height_);
    filtered_image_.allocate(width_, height_);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}
