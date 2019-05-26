#include "editor-graph.h"

 
EditorGraph::EditorGraph(wxWindow* parent) :
wxPanel(parent)
{
	
}


void EditorGraph::render(wxDC&  dc)
{
	DrawAxes(dc);
	DrawCurrentPointsOnGraph(dc);
}

void EditorGraph::mouseDownLeftClick()
{
	std::cout << "mouse down left click called! \n";
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

void EditorGraph::DrawAxes(wxDC& dc)
{
	
}
