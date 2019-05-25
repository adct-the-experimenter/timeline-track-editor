#include "double-track.h"

DoubleTrack::DoubleTrack(const wxString& title)  : Track (title)
{
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(DoubleTrack::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(DoubleTrack::OnSize));
}


void DoubleTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}

void DoubleTrack::InitTrack(wxWindow* parent)
{
	Track::InitTrack(parent);
	
	wxStaticText *st1 = new wxStaticText(this, wxID_ANY, wxT("This is a double track."), wxPoint(25, 80) );
}

void DoubleTrack::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void DoubleTrack::OnScroll(wxScrollEvent& event)
{
	//std::cout << "Scroll called! \n";
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}


void DoubleTrack::OnPaint(wxPaintEvent& event)
{
	//std::cout << "Current Time in Track:" << *current_time_pos_pointer << std::endl;
	
}

double DoubleTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void DoubleTrack::SetReferenceToVarToManipulate(double* thisVar){varToManipulatePtr = thisVar;}
