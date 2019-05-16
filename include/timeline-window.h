#ifndef TIMELINE_WINDOW_H
#define TIMELINE_WINDOW_H

#include <wx/wx.h>
#include <wx/slider.h>

#include <iostream>

//number in units of pixels
enum
    {
        TRACK_WIDTH = 792,
        TRACK_HEIGHT = 297,
        SLIDER_START_X = 50
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
	int max_timeline_size;
	
};


// Frame that contains Timeline scrolling window
class TimelineFrame : public wxFrame
{
public:
    TimelineFrame(wxWindow *parent);
};




const int ID_SLIDER = 100;

#endif
