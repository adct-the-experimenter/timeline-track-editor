#include "editor-graph.h"

 
EditorGraph::EditorGraph(wxWindow* parent) :
wxPanel(parent)
{
	
}

void EditorGraph::SetReferenceToTimeTickVector(std::vector <int> *thisVector){timeTickVectorPtr = thisVector;}

template <typename T>
void EditorGraph::render(wxDC&  dc,std::vector <T> *verticalAxisVector)
{
	DrawHorizontalAxis(dc);
	DrawVerticalAxis(dc,verticalAxisVector);
	DrawCurrentPointsOnGraph(dc);
}

template void EditorGraph::render<double>( wxDC& , std::vector<double>*);

void EditorGraph::DrawHorizontalAxis(wxDC& dc)
{
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	int step = (int) round( TRACK_WIDTH / (TIME_TICK_NUM-1) );
	int offset = TRACK_WIDTH / (TIME_TICK_NUM - 1);
	
	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= (int)timeTickVectorPtr->size(); i++ ) 
	{
		dc.DrawLine(i*step - offset, 1, i*step - offset , 10);
		dc.DrawText( wxString::Format( wxT("%ds"), (int)timeTickVectorPtr->at(i-1) ) , i*step - offset, 10);
	}
}

template <typename T>
void EditorGraph::DrawVerticalAxis(wxDC& dc,std::vector <T> *verticalAxisVector)
{
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	int step = (int) round( TRACK_HEIGHT / (verticalAxisVector->size()) );

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( size_t i=1; i <= verticalAxisVector->size(); i++ ) 
	{
		dc.DrawLine(1, i*step, 10, i*step);
		//start at end to draw positive numbers on top
		dc.DrawText( wxString::Format( wxT("%d"), (int)verticalAxisVector->at(verticalAxisVector->size() - i) ) , 0, (i*step) - 10);
	}
}

template void EditorGraph::DrawVerticalAxis<double>( wxDC& , std::vector<double>*);

void EditorGraph::mouseDownLeftClick()
{
	EditorGraph::PlacePointByMouse();
}

void EditorGraph::PlacePointByMouse()
{
	//get graphical coordinates of where mouse left clicked relative to track panel
	int mouseX = wxGetMousePosition().x - this->GetScreenPosition().x; 
	int mouseY = wxGetMousePosition().y - this->GetScreenPosition().y;
	
	//convert mouse x to time value
	double thisTime = mouseX * ((double)TIME_END_VALUE / (double)TRACK_WIDTH);
	
	//check if there is already a point at that time value
	if ( map_time.find(thisTime) == map_time.end() ) 
	{
	  //if not found 
	  //put into vector of graph points
	  graph_points.push_back( wxPoint(mouseX,mouseY) );
	  //put into time map
	  std::vector<wxPoint>::iterator it = graph_points.end();
	  map_time.emplace(thisTime, it);
	} 
		
	
}

void EditorGraph::DrawCurrentPointsOnGraph(wxDC& dc)
{
	// draw a circle
    dc.SetBrush(*wxBLACK_BRUSH);
    for(size_t i=0; i < graph_points.size(); i++)
    {
		dc.DrawCircle( graph_points.at(i), 2 );
	}
    
    
}
