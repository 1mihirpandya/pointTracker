#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
    ofBackground(0,0,0);
	
    camWidth 		= 640;	// try to grab at this size.
    camHeight 		= 480;
    track_ = false;
    previous_points_ = {20.0,20.0};
    points_ = {20.0,20.0};
    ofSetBackgroundAuto(false);
	vidGrabber.setVerbose(true);
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
    if (track_) {
        std::cout << previous_points_[0] << " " << previous_points_[1] << std::endl;
        std::cout << points_[0] << " " << points_[1] << std::endl;
        std::cout << "" << std::endl;
        ofDrawLine(previous_points_[0], previous_points_[1], points_[0], points_[1]);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
    if (key == 'f' || key == 'F'){
        // Draw some shapes
        track_ = true;
        points_[0] += 100;
        points_[1] += 100;
        draw();
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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
