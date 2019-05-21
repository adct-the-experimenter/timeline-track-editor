#ifndef TRACK_H
#define TRACK_H

#include <wx/wx.h>
#include <wx/slider.h>

#include <iostream>
#include <vector>


class Track : public wxFrame
{
public:
    Track(const wxString& title);
    
    virtual void InitTrack(wxWindow* parent);

    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    
    wxWindow* getWindowReference();
    
private:
	
	wxString m_title; //title of the track
	
	wxSlider* time_slider;
    double* current_time_pos_pointer;
    
    const int ID_CHECKBOX = 100;
    
};

#endif
