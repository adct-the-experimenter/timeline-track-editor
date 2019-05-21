#include "track.h"

Track::Track(const wxString& title)  : wxFrame()
{
	m_title = title;
}


void Track::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){current_time_pos_pointer = thisTimeVariable;}

void Track::InitTrack(wxWindow* parent)
{
	this->Create(parent, wxID_ANY, m_title, wxDefaultPosition, wxSize(270, 150));
	
	wxStaticText *st1 = new wxStaticText(parent, wxID_ANY, wxT("This is a track."), wxPoint(25, 80) );
	
}

void Track::OnSize(wxSizeEvent& event)
{
	//m_window->Refresh();

	//m_window->FitInside();
}

void Track::OnScroll(wxScrollEvent& event)
{
	std::cout << "Scroll called! \n";
	//m_window->Refresh(); //for wxDc onPaint stuff 
	
	//m_window->FitInside(); //for scroll and sizer
}


void Track::OnPaint(wxPaintEvent& event)
{
	
}

