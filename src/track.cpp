#include "track.h"

Track::Track(const wxString& title)  : wxPanel()
{
	m_title = title;
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(Track::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(Track::OnSize));
}


void Track::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){current_time_pos_pointer = thisTimeVariable;}

void Track::InitTrack(wxWindow* parent)
{
	m_parent = parent;
	
	this->Create(parent, wxID_ANY, wxDefaultPosition, wxSize(TRACK_WIDTH, TRACK_HEIGHT),wxTAB_TRAVERSAL,m_title);
	this->SetBackgroundColour( *wxLIGHT_GREY );
	this->Show();
	wxStaticText *st1 = new wxStaticText(this, wxID_ANY, wxT("This is a track."), wxPoint(25, 80) );
}

void Track::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void Track::OnScroll(wxScrollEvent& event)
{
	//std::cout << "Scroll called! \n";
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}


void Track::OnPaint(wxPaintEvent& event)
{
	std::cout << "Current Time in Track:" << *current_time_pos_pointer << std::endl;
}

