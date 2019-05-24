#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>

enum
    {
        TRACK_WIDTH = 1000, // width,in pixels, of the track 
        TRACK_HEIGHT = 297, //height,in pixels, of the track 
        
        TIME_START_VALUE = 0, //start value, in seconds, of ruler and track time
        TIME_END_VALUE = 100, //end value, in seconds, of ruler and track time
        TIME_RESOLUTION = 100,  //resolution, in milliseconds, of playback timer and track timer. i.e. if TIME_RESOLUTION=0.1s, only move forward by 0.1s in playback
        
        TIME_TICK_NUM = 11, //number of ticks to display in ruler, make sure to include zero
        VERTICAL_LINE_HEIGHT_TIME = 400 //height,in pixels, of the vertical line showing current time position 
    };
    
#endif
