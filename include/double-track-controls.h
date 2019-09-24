#ifndef DOUBLETRACK_CONTROLS_H
#define DOUBLETRACK_CONTROLS_H

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/timer.h>

#include <iostream>
#include <vector>

class DoubleTrackControls
{
public:

	DoubleTrackControls(wxWindow* parent, wxBoxSizer* hbox);
	//must pass a external box sizer or else segfault happens from double track deleting a box sizer that
	//timeline window owns when it is added to the timeline window 
	~DoubleTrackControls();
	
private:
	
	
	
	wxButton *zoomInTimeButton;
    wxButton *zoomOutTimeButton;
    wxButton *zoomInVerticalButton;
    wxButton *zoomOutVerticalButton;
     
};

#endif
