#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

    ofSetupOpenGL(ofApp::default_width, ofApp::default_height, OF_WINDOW);			// <-------- setup the GL context
	ofRunApp( new ofApp());

}
