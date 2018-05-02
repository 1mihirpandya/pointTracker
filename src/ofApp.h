#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include <cmath>
#include <stdlib.h>

class ofApp : public ofBaseApp{
    
    std::vector<ofPath*> user_lines_;
    ofPath *current_line_;
    int point_onscreen_;
    ofVideoGrabber video_;
    int width_;
    int height_;
    ofxColorSlider color_slider_;
    bool settings_active_;
    std::vector<int> line_color_;
    ofColor target_color_;
    ofxCvColorImage rgb_image_,hsb_image_;
    ofxCvGrayscaleImage hue_image_,saturation_image_,brightness_image_,filtered_image_;
    ofxCvContourFinder contours_;
    int target_hue_;
    bool shape_set_;
    std::vector<int> current_points_;
    std::vector<float> shape_area_;
    char shape_type_;
public:
    //a line drawn solely via keyboard
    void setup();
    void update();
    void setupTrackingFunctionality(int width, int height);
    void setupDrawingFunctionality();
    std::vector<int> applyEuclidianFormula();
    void newShape(char shape_type);
    void findPoint();
    void draw();
    void newLine();
    void addPoint(int x, int y);
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
};
