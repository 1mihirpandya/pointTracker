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
    mouse_line_.draw();
    keyboard_line_.draw();
//    if (track_) {
//        std::cout << previous_points_[0] << " " << previous_points_[1] << std::endl;
//        std::cout << points_[0] << " " << points_[1] << std::endl;
//        std::cout << "" << std::endl;
//        ofDrawLine(previous_points_[0], previous_points_[1], points_[0], points_[1]);
//    }
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //updates the point and adds the vertex to the line
    ofPoint point;
    if (key == 'd' || key == 'D'){
        points_[0] += 100;
    }
    if (key == 's' || key == 'S'){
        points_[1] += 100;
    }
    if (key == 'w' || key == 'W'){
        points_[1] -= 100;
    }
    if (key == 'a' || key == 'A'){
        points_[0] -= 100;
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
    mouse_line_.addVertex(point);
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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
