#ifndef TIMELINE_WINDOW_H
#define TIMELINE_WINDOW_H

#include <wx/wx.h>
#include <wx/slider.h>

#include <iostream>
#include <vector>

enum
    {
        TRACK_WIDTH = 1000, //in pixels
        TRACK_HEIGHT = 297, //in pixels
        TIME_START_VALUE = 0, //start value of ruler
        TIME_END_VALUE = 100, //end value of ruler
        TIME_TICK_NUM = 11, //number of ticks to display in ruler, make sure to include zero
        VERTICAL_LINE_HEIGHT_TIME = 400 //in pixels
    };

class TimelineWindow : public wxScrolled<wxWindow>
{
public:
    TimelineWindow(wxWindow *parent);

    void OnPaint(wxPaintEvent& event);
    void OnScroll(wxScrollEvent& event);
	void OnSize(wxSizeEvent& event);
    
private:
	
	wxSlider *m_slider;
    int m_slider_value;
    
	std::vector <int> m_time_num; // numbers to display on ruler
	int slider_start_x_pos; //pixel x position of slider set based on ticks
	
	void InitTimeline(); //function to initialize parameters for timeline
	
	void InitTimeVector(); //function to initialze m_time_num
	std::vector<double> LinearSpacedArray(double a, double b, std::size_t N);
	
};


// Frame that contains Timeline scrolling window
class TimelineFrame : public wxFrame
{
public:
    TimelineFrame(wxWindow *parent);
};




const int ID_SLIDER = 100;

#endif
