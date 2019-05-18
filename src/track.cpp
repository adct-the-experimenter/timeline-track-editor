#include "track.h"

Track::Track() 
{
	
}

void Track::InitTrack(wxWindow* parent)
{
	m_window = new wxScrolled<wxWindow>(parent, wxID_ANY);
	
	wxCheckBox *m_cb; 
	m_cb = new wxCheckBox(m_window, ID_CHECKBOX, wxT("Show title"), wxPoint(20, 20));
	m_cb->SetValue(true);
}

wxWindow* Track::getWindowReference(){return m_window;}

void Track::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){current_time_pos_pointer = thisTimeVariable;}

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

