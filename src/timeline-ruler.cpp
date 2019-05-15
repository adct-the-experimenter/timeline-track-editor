#include "timeline-ruler.h"

TimelineSlider::TimelineSlider(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, 
       wxSize(270, 200))
{
  panel = new TimelinePanel(this);
  Center();
}


TimelinePanel::TimelinePanel(wxFrame * parent)
       : wxPanel(parent, wxID_ANY)
{
  fill = 0;
  slider = new wxSlider(this, ID_SLIDER, 0, 0, 140, wxPoint(50, 30), 
      wxSize(150, -1), wxSL_HORIZONTAL);

  Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TimelinePanel::OnScroll));  
  Connect(wxEVT_PAINT, wxPaintEventHandler(TimelinePanel::OnPaint));

}

void TimelinePanel::OnScroll(wxScrollEvent& event)
{
  fill = slider->GetValue();
  Refresh();
}

void TimelinePanel::OnPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);

  wxPen pen(wxColour(212, 212, 212));
  dc.SetPen(pen);
  
  wxBrush brush1(wxColour(197, 108, 0));
  dc.SetBrush(brush1);
  
  wxCoord x = 55 + fill;
  
  dc.DrawRectangle( wxRect(x, 0, 2, 200) );
}
