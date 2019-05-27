#include "double-track.h"

DoubleTrack::DoubleTrack(const wxString& title)  : Track (title)
{
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(DoubleTrack::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(DoubleTrack::OnSize));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(DoubleTrack::OnLeftMouseClick));
	Connect(wxEVT_CONTEXT_MENU, wxCommandEventHandler(DoubleTrack::OnRightMouseClick));
}

void DoubleTrack::FunctionToCallEveryTimeInTimerLoop()
{
	if(varToManipulatePtr != nullptr)
	{
		if(graphEditor != nullptr)
		{
			double thisTime = DoubleTrack::GetCurrentTime();
			
			//check if there is  a point at that time value
			if ( map_time_output.find(thisTime) == map_time_output.end() ) 
			{
				//if not found, do nothing
			}
			else
			{
				//if found

				//get iterator to vector from time map
				std::unordered_map<double,double>::const_iterator got = map_time_output.find (thisTime);
				
				//std::cout << "value " << got->second << " found at time " << got->first << std::endl;
				*varToManipulatePtr = got->second;
			}
		}
	}
}

void DoubleTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}

std::vector <int> * DoubleTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

void DoubleTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){Track::SetReferenceToTimeTickVector(thisVector);}

void DoubleTrack::SetReferenceToVarToManipulate(double* thisVar){varToManipulatePtr = thisVar;}

double DoubleTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void DoubleTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	Track::InitTrack(parent,timeTickVector);
	
	graphEditor = new EditorGraph(this);
	graphEditor->SetReferenceToTimeTickVector(timeTickVector);
	
	//wxStaticText *st1 = new wxStaticText(this, wxID_ANY, wxT("This is a double track."), wxPoint(25, 80) );
}

void DoubleTrack::SetupAxisForVariable(double& start, double& end,double& resolution, int& numTick)
{
	verticalStart = start;
	verticalEnd = end;
	verticalNumTicks = numTick;
	verticalResolution = resolution;
	
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
	double mouseTimePoint; 
	int mouseYPoint;
	bool legitValues = true;
	
	graphEditor->mouseDownLeftClick(verticalStart,verticalEnd,verticalResolution,
									mouseTimePoint, mouseYPoint,legitValues);
	
	if(legitValues)
	{
		//convert mouse y point to output value
		double output = ((double)TRACK_HEIGHT - mouseYPoint) * ((verticalEnd - verticalStart) / double(TRACK_HEIGHT) ) - verticalEnd;
		
		//put it in the map
		map_time_output.emplace(mouseTimePoint, output);
	}
	event.Skip();
}

void DoubleTrack::OnRightMouseClick(wxCommandEvent& event)
{
	double mouseTimePoint;
	bool legitValue = true;
	
	graphEditor->mouseDownRightClick(mouseTimePoint, legitValue);
	
	if(legitValue)
	{
		//remove point from the map
		map_time_output.erase(mouseTimePoint);
	}
	event.Skip();
}


