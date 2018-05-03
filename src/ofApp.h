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
    std::vector<ofPath*> user_objects_;
    ofPath *current_object_;
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
    int missing_point_frame_counter_;
    int target_hue_;
    bool set_shape_;
    char shape_type_;
    
public:
    //functions that set up the application
    void setup();
    void setupTrackingFunctionality(int width, int height);
    void setupDrawingFunctionality();
    //drawing/line editing functions
    void draw();
    void newObject();
    void newShape(char shape_type);
    void addPoint(int x, int y);
    void setShape();
    //point tracking functions
    void update();
    void findPotentialPoints();
    std::vector<int> applyEuclidianFormula();
    //built in functions used in the application
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
    //constants
    const int color_picker_size = 64;
    const int max_missing_point_counter = 20;
    const int rectangle_height = 100;
    const int rectangle_width = 50;
    const int circle_radius = 50;
    const int triangle_offset = 50;
    const int depth_threshold = 300;
    const int hue_threshold = 5;
    const int line_width = 5;
    const int min_contour_area = 50;
    const int default_height = 720;
    const int default_width = 1320;
    char rectangle = 'r';
    char circle = 'c';
    char triangle = 't';
};
