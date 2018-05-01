#include "ofApp.h"

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
    //current_line_->setFilled(false);
    //ofSetBackgroundAuto(false);
    vidGrabber.setup(camWidth,camHeight);
    ofEnableAlphaBlending();
    settings_active_ = false;
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    int intended_red = 0;
    int intended_green = 200;
    int intended_blue = 50;
    
    float min_difference = 255;
    int approx_x = 0;
    int approx_y = 0;
    ofPixelsRef screen = vidGrabber.getPixels();
    for (int i = 0; i < camWidth; i+= 1){
        for (int j = 0; j < camHeight; j+= 1){
            ofColor color = screen.getColor(i, j);
            float r_difference = color.r - intended_red;
            float g_difference = color.g - intended_green;
            float b_difference = color.b - intended_blue;
            float color_difference = sqrt(r_difference * r_difference + r_difference * r_difference + r_difference * r_difference);
            if(color_difference < min_difference){
                min_difference = color_difference;
                approx_x = i;
                approx_y = j;
            }
            //if (color.r <= 20 && color.g >= 100 ) {
            //    addPoint(i,j);
            //    point_onscreen = 0;
            //    break;
            //}
        }
    }
    if (screen.getColor(approx_x, approx_y).r <= 20 && screen.getColor(approx_x, approx_y).g >= 70 ) {
        addPoint(approx_x, approx_y);
        point_onscreen = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //vidGrabber.draw(vidGrabber.getWidth(),0,-vidGrabber.getWidth(),vidGrabber.getHeight());
    vidGrabber.draw(0,0);
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
    //    if (track_) {
    //        std::cout << previous_points_[0] << " " << previous_points_[1] << std::endl;
    //        std::cout << points_[0] << " " << points_[1] << std::endl;
    //        std::cout << "" << std::endl;
    //        ofDrawLine(previous_points_[0], previous_points_[1], points_[0], points_[1]);
    //    }
}

void ofApp::newLine() {
    //std::cout << "making new line" << std::endl;
    user_lines_.push_back(new ofPath());
    current_line_ = user_lines_.back();
    //std::cout << user_lines_.size() << std::endl;
    //std::cout << "" << std::endl;
}

void ofApp::addPoint(int x, int y) {
    ofPoint point;
    point.set(x,y);
    //current_line_->addVertex(point);
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
        //ofPolyline *line_to_delete;
        for (int x = 0; x < user_lines_.size(); x++) {
            (user_lines_.at(x))->clear();
            user_lines_.erase(user_lines_.begin() + x);
            user_lines_.clear();
            newLine();
            //delete line_to_delete;
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
