#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    point_onscreen = 0;
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    user_lines_.push_back(ofPolyline());
    current_line_ = &user_lines_.back();
    ofSetBackgroundAuto(false);
    vidGrabber.setup(camWidth,camHeight);
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vidGrabber.draw(0,0);
    ofPixelsRef screen = vidGrabber.getPixels();
    for (auto line : user_lines_) {
        line.draw();
    }
    
    for (int i = 0; i < camWidth; i+= 1){
        for (int j = 0; j < camHeight; j+= 1){
            ofColor color = screen.getColor(i, j);
            if (color.r <= 20 && color.g >= 100 ) {
                addPoint(i,j);
                point_onscreen = 0;
                break;
            }
        }
    }
    if (point_onscreen == 0)
    {
        current_line_->draw();
        point_onscreen += 1;
    } else {
        if (point_onscreen == 5) {
        newLine();
        } else {
            point_onscreen += 1;
        }
    }
    std::cout << point_onscreen << std::endl;
    //    if (track_) {
    //        std::cout << previous_points_[0] << " " << previous_points_[1] << std::endl;
    //        std::cout << points_[0] << " " << points_[1] << std::endl;
    //        std::cout << "" << std::endl;
    //        ofDrawLine(previous_points_[0], previous_points_[1], points_[0], points_[1]);
    //    }
    
}

void ofApp::newLine() {
    user_lines_.push_back(ofPolyline());
    current_line_ = &(user_lines_.back());
}

void ofApp::addPoint(int x, int y) {
    ofPoint point;
    point.set(x,y);
    current_line_->addVertex(point);
}
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //updates the point and adds the vertex to the line
    ofPoint point;
    if (key == 'c' || key == 'C'){
        //delete user_lines_;
        ofPolyline *line_to_delete;
        std::cout << user_lines_.size() << std::endl;
        for (int x = user_lines_.size() - 1; x >= 0; x--) {
            if (typeid(user_lines_.at(x)) != typeid(ofPolyline)) {
                std::cout << "not" << std::endl;
                user_lines_.at(x) = ofPolyline();
            }
            line_to_delete = &(user_lines_.at(x));
            line_to_delete->clear();
            //delete line_to_delete;
        }
        std::cout << user_lines_.size() << std::endl;
    }
    if (key == 'b' || key == 'B') {
        current_line_->clear();
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
