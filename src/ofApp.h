#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include <cmath>
#include <stdlib.h>

class ofApp : public ofBaseApp{
    int width_;
    int height_;
    //variables related to drawing
    std::vector<ofPath*> user_lines_;
    ofPath *current_line_;
    ofxColorSlider color_slider_;
    bool settings_active_;
    //variables related to video and point tracking
    std::vector<int> current_points_;
    std::vector<float> shape_area_;
    ofVideoGrabber video_;
    ofxCvColorImage rgb_image_;
    ofxCvColorImage hsb_image_;
    ofxCvGrayscaleImage hue_image_;
    ofxCvGrayscaleImage saturation_image_;
    ofxCvGrayscaleImage brightness_image_;
    ofxCvGrayscaleImage filtered_image_;
    ofxCvContourFinder contours_;
    ofColor target_color_;
    int point_onscreen_;
    int target_hue_;
    bool shape_set_;
    char shape_type_;
public:
    //functions that set up the application
    void setup();
    void setupTrackingFunctionality(int width, int height);
    void setupDrawingFunctionality();
    //drawing/line editing functions
    void draw();
    void newLine();
    void newShape(char shape_type);
    void addPoint(int x, int y);
    void setShape();
    //point tracking functions
    void update();
    void findPoint();
    std::vector<int> applyEuclidianFormula();
    //built in functions used in the application
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
};
