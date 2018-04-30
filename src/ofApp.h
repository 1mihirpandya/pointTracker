#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
    std::vector<ofPolyline*> user_lines_;
    ofPolyline *current_line_;
    int point_onscreen;
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
public:
    //a line drawn solely via keyboard
    void setup();
    void update();
    void draw();
    void newLine();
    void addPoint(int x, int y);
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
};
