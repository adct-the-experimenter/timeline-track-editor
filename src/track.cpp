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
	//std::cout << "OnPaint called in Track.\n";
	wxPaintDC dc(this);

	//DoPrepareDC(dc); //prepare device context for drawing a scrolling image
	
	//Initialize variables for drawing vertical timeline line indicating current position
	wxPen pen(wxColour(212, 212, 212));
	dc.SetPen(pen);
	
	wxBrush brush1(wxColour(197, 108, 0));
	dc.SetBrush(brush1);
	
	//initialize variables for timeline ruler
	
	int step = (int) round( TRACK_WIDTH / (TIME_TICK_NUM-1) );

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= 00; i++ ) 
	{
		dc.DrawLine(i*step, 1, i*step, 10);
		//dc.DrawText( wxString::Format( wxT("%ds"), m_time_num[i-1] ) , i*step, 10);
	}
	
}

