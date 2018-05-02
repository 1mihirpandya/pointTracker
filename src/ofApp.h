#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
    
    std::vector<ofPath*> user_lines_;
    ofPath *current_line_;
    int point_onscreen;
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    ofxColorSlider color_slider_;
    bool settings_active_;
    std::vector<int> line_color_;
    ofColor targetColor;
    ofPoint tester;
    ofxCvColorImage rgb,hsb;
    ofxCvGrayscaleImage hue,sat,bri,filtered;
    ofxCvContourFinder contours;
    int findHue;
    bool shape_set_;
    std::vector<int> current_points_;
    std::vector<float> shape_area_;
public:
    //a line drawn solely via keyboard
    void setup();
    void update();
    std::vector<int> applyEuclidianFormula();
    void newShape();
    void findPoint();
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
