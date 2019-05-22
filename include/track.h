#ifndef TRACK_H
#define TRACK_H

#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/panel.h>

#include <iostream>
#include <vector>

#include "parameters.h"

class Track : public wxPanel
{
public:
    Track(const wxString& title);
    
    virtual void InitTrack(wxWindow* parent);

    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    
private:
	
	wxWindow* m_parent;
	
	wxString m_title; //title of the track
	
	wxSlider* time_slider;
    double* current_time_pos_pointer;
    
};

#endif
