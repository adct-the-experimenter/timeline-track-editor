#include "double-track.h"

DoubleTrack::DoubleTrack(const wxString& title)  : Track (title)
{
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(DoubleTrack::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(DoubleTrack::OnSize));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(DoubleTrack::OnLeftMouseClick));
}


void DoubleTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}

std::vector <int> * DoubleTrack::GetReferenceToTimeTickVector(){Track::GetReferenceToTimeTickVector();}

void DoubleTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){Track::SetReferenceToTimeTickVector(thisVector);}

void DoubleTrack::SetReferenceToVarToManipulate(double* thisVar){varToManipulatePtr = thisVar;}

double DoubleTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void DoubleTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	Track::InitTrack(parent,timeTickVector);
	
	graphEditor = new EditorGraph(this);
	graphEditor->SetReferenceToTimeTickVector(timeTickVector);
	
	wxStaticText *st1 = new wxStaticText(this, wxID_ANY, wxT("This is a double track."), wxPoint(25, 80) );
}

void DoubleTrack::SetBoundsForVariable(double& start, double& end, int& numTick)
{
	verticalStart = start;
	verticalEnd = end;
	verticalNumTicks = numTick;
	
	//setup tick marks
	DoubleTrack::InitVerticalAxis();
}

void DoubleTrack::InitVerticalAxis()
{
	//get linearly spaced vector of doubles
	std::vector <double> thisVector = DoubleTrack::LinearSpacedArray(verticalStart,verticalEnd,(size_t)verticalNumTicks);
	
	for(size_t i=0; i < thisVector.size(); ++i)
	{
		m_vertical_var_num.push_back(thisVector[i]);
	}
}

std::vector<double> DoubleTrack::LinearSpacedArray(double a, double b, std::size_t N)
{
	// Linear interpolation following MATLAB linspace
	double h = (b - a) / static_cast<double>(N-1);
	std::vector<double> xs(N);
	std::vector<double>::iterator x;
	double val;
	for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) {
		*x = val;
	}
	return xs;
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
	wxPaintDC dc(this);

	PrepareDC(dc); //prepare device context for drawing a scrolling image
	
	graphEditor->render(dc,&m_vertical_var_num);
	
	Refresh();
}

void DoubleTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	graphEditor->mouseDownLeftClick();
	event.Skip();
}


