//
//  pointTrackerConstants.h
//  pointTracker
//
//  Created by Mihir Pandya on 5/2/18.
//

#ifndef pointTrackerConstants_h
#define pointTrackerConstants_h
namespace pointTracker {
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
}

#endif /* pointTrackerConstants_h */
