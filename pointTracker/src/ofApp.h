#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	
	public:
        //tracks points for the keyboard line
        std::vector<float> points_;
        //a line drawn solely via keyboard
        ofPolyline keyboard_line_;
        //a line drawn solely via mouse dragging
        ofPolyline mouse_line_;
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber 		vidGrabber;
		int 				camWidth;
		int 				camHeight;
    
        string asciiCharacters;
        ofTrueTypeFont  font;
    
    
};
