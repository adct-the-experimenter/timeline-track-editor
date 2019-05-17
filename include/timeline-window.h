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
        SLIDER_START_X = 100, //in pixels
        SLIDER_START_VALUE = 0, 
        SLIDER_END_VALUE = 100, //does not yet work for values other than 100, slider offset fails
        VERTICAL_LINE_HEIGHT_TIME = 400 //in pixels
    };

class TimelineWindow : public wxScrolled<wxWindow>
{
public:
    TimelineWindow(wxWindow *parent);

    void OnPaint(wxPaintEvent& event);
    void OnScroll(wxScrollEvent& event);
	void OnSize(wxSizeEvent& event);
	
    wxSlider *slider;
    int m_slider_value;
private:
	std::vector <int> m_time_num; // numbers to display on ruler
};


// Frame that contains Timeline scrolling window
class TimelineFrame : public wxFrame
{
public:
    TimelineFrame(wxWindow *parent);
};




const int ID_SLIDER = 100;

#endif
