#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
	
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    points_ = {0.0,0.0};
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
    for (auto line : mouse_lines_) {
        line.draw();
    }
    
    std::vector<std::vector<int>> pointTracker;
    for (int i = 0; i < camWidth; i+= 1){
        for (int j = 0; j < camHeight; j+= 1){
            ofColor color = screen.getColor(i, j);
            if (color.r <= 20 && color.g >=150 ) {
                addPoint(i,j, &pointTracker);
                break;
            }
            
            
        }}
    keyboard_line_.draw();
//    if (track_) {
//        std::cout << previous_points_[0] << " " << previous_points_[1] << std::endl;
//        std::cout << points_[0] << " " << points_[1] << std::endl;
//        std::cout << "" << std::endl;
//        ofDrawLine(previous_points_[0], previous_points_[1], points_[0], points_[1]);
//    }
    
}

void ofApp::addPoint(int x, int y, std::vector<std::vector<int>> *pointTracker) {
    ofPoint point;
    point.set(x,y);
    keyboard_line_.addVertex(point);
}
//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //updates the point and adds the vertex to the line
    ofPoint point;
    if (key == 'c' || key == 'C'){
        //keyboard_line_.close();
        //delete &keyboard_line_;
        //keyboard_line_ = ofPolyline();
    }
    if (key == 's' || key == 'S'){
        points_[1] += 10;
    }
    if (key == 'w' || key == 'W'){
        points_[1] -= 10;
    }
    if (key == 'a' || key == 'A'){
        points_[0] -= 10;
    }
    point.set(points_[0],points_[1]);
    keyboard_line_.addVertex(point);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //updates the mouse line based on the mouse's new position
    ofPoint point;
    point.set(x,y);
    mouse_lines_.back().addVertex(point);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouse_lines_.push_back(ofPolyline());
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    //mouse_lines_ = ofPolyline();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
