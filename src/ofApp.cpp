#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    point_onscreen = 0;
    camWidth = 640;	// try to grab at this size.
    camHeight = 480;
    user_lines_.push_back(new ofPath());
    current_line_ = user_lines_.back();
    color_slider_.setup("Pick the line color you want!",ofColor(), ofColor(), 20, 300);
    current_line_->setMode(ofPath::POLYLINES);
    current_line_->setFilled(false);
    current_line_->setStrokeWidth(5);
    current_line_->setColor(color_slider_);
    ofSetBackgroundAuto(false);
    vidGrabber.setup(camWidth,camHeight);
    ofEnableAlphaBlending();
    settings_active_ = false;
    rgb.allocate(camWidth, camHeight);
    hsb.allocate(camWidth, camHeight);
    hue.allocate(camWidth, camHeight);
    sat.allocate(camWidth, camHeight);
    bri.allocate(camWidth, camHeight);
    filtered.allocate(camWidth, camHeight);
    findHue = -1;
}


//--------------------------------------------------------------
//http://beriomolina.com/Tracking-colors-tracking-laser/
//https://sites.google.com/site/ofauckland/examples/10-testing
void ofApp::update(){
    vidGrabber.update();
    if (vidGrabber.isFrameNew()) {
        rgb.setFromPixels(vidGrabber.getPixels());
        rgb.resize(camWidth, camHeight);
        rgb.mirror(false, true);
        hsb = rgb;
        hsb.convertRgbToHsv();
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        if (findHue > -1) {
        for (int i=0; i<camWidth * camHeight; i++) {
            filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],findHue-5,findHue+5) ? 255 : 0;
        }
        filtered.flagImageChanged();
        //run the contour finder on the filtered image to find blobs with a certain hue
        contours.findContours(filtered, 50, camWidth * camHeight/2, 1, false);
        float min_difference = 255;
        int approx_x = -1;
        int approx_y = -1;
        ofPixelsRef screen = vidGrabber.getPixels();
        for (int i=0; i<contours.nBlobs; i++) {
                    ofColor color = screen.getColor(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y);
                    float r_difference = color.r - targetColor.r;
                    float g_difference = color.g - targetColor.g;
                    float b_difference = color.b - targetColor.b;
                    float color_difference = sqrt(r_difference * r_difference + r_difference * r_difference + r_difference * r_difference);
                    if(color_difference < min_difference){
                        min_difference = color_difference;
                        approx_x = contours.blobs[i].centroid.x;
                        approx_y = contours.blobs[i].centroid.y;
                    }
        }
            if (approx_x > -1 && approx_y > -1) {
        addPoint(approx_x, approx_y);
        point_onscreen = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //vidGrabber.draw(vidGrabber.getWidth(),0,-vidGrabber.getWidth(),vidGrabber.getHeight());
    rgb.draw(0,0);
    if (settings_active_){
        color_slider_.draw();
    }
    for (auto &line : user_lines_) {
        line->draw();
    }
    if (point_onscreen == 0)
    {
        current_line_->draw();
        point_onscreen += 1;
    } else {
        if (point_onscreen == 20) {
            newLine();
            point_onscreen = 21;
        } else {
            point_onscreen += 1;
        }
    }
    ofPath x;
    x.setFilled(true);
    x.setColor(targetColor);
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
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //updates the point and adds the vertex to the line
    ofPoint point;
    if (key == 'c' || key == 'C'){
        for (int x = 0; x < user_lines_.size(); x++) {
            (user_lines_.at(x))->clear();
            user_lines_.erase(user_lines_.begin() + x);
            user_lines_.clear();
            newLine();
        }
    }
    if (key == 'b' || key == 'B') {
        current_line_->clear();
    }
    if (key == 's' || key == 'S') {
        settings_active_ = !settings_active_;
        if (!settings_active_) {
            current_line_->setColor(color_slider_);
        }
    }
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

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    std::cout << targetColor << std::endl;
    //calculate local mouse x,y in image
    int mx = x % camWidth;
    int my = y % camHeight;
    targetColor = vidGrabber.getPixels().getColor(mx, my);
    //get hue value on mouse position
    findHue = hue.getPixels()[my * camWidth + mx];
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
void ofApp::windowResized(int w, int h){
    camWidth = w;
    camHeight = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}
