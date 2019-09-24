#include "double-track-controls.h"

DoubleTrackControls::DoubleTrackControls(wxWindow* parent, wxBoxSizer* hbox)
{
	zoomInTimeButton = new wxButton(parent, wxID_NEW, wxT("Zoom In Time"));
    zoomOutTimeButton = new wxButton(parent, wxID_NEW, wxT("Zoom Out Time"));
    zoomInVerticalButton = new wxButton(parent, wxID_NEW, wxT("Zoom In Vertical"));
    zoomOutVerticalButton = new wxButton(parent, wxID_NEW, wxT("Zoom Out Vertical"));
    
    hbox->Add(zoomInTimeButton, 0,  wxALL, 0);
    hbox->Add(zoomOutTimeButton, 0,  wxALL, 0);
    hbox->Add(zoomInVerticalButton, 0,  wxALL, 0);
    hbox->Add(zoomOutVerticalButton, 0,  wxALL, 0);    
}

DoubleTrackControls::~DoubleTrackControls()
{
	if(zoomInTimeButton){delete zoomInTimeButton;}
    if(zoomOutTimeButton){delete zoomOutTimeButton;}
    if(zoomInVerticalButton){delete zoomInVerticalButton;}
    if(zoomOutVerticalButton){delete zoomOutVerticalButton;}
}
