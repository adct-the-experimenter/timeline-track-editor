#ifndef TIMELINE_WINDOW_H
#define TIMELINE_WINDOW_H

#include <wx/wx.h>
#include <wx/slider.h>


enum
    {
        // these numbers are not multiple of 10 (our scroll step) to test for
        // the absence of rounding errors (e.g. we should have one more page
        // than WIDTH/10 to show the right side of the rectangle)
        WIDTH = 792,
        HEIGHT = 297
    };

class TimelineWindow : public wxScrolled<wxWindow>
{
public:
    TimelineWindow(wxWindow *parent);

    void OnPaint(wxPaintEvent& event);
    void OnScroll(wxScrollEvent& event);
	void OnSize(wxSizeEvent& event);
	
    wxSlider *slider;
    int fill;
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
