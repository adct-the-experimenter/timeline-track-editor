#include "wx/wx.h"
#include "wx/sizer.h"

#include "parameters.h"

#include <vector>
#include <unordered_map>

#include <wx/dcbuffer.h>

class EditorGraph : public wxPanel
{

public:
    EditorGraph(wxWindow* parent);
    
    void mouseDownLeftClick();
    
    void render(wxDC& dc);
    
   

private:
	
	std::vector <wxPoint> graph_points; //holds points drawn on graph
	
	std::unordered_map <double, std::vector<wxPoint>::iterator> map_time; //dictionary to keep track of which time values are occupied
	
	//function to place point on mouse event
	void PlacePointByMouse();
	
	//function to draw graph_points on graph
	void DrawCurrentPointsOnGraph(wxDC& dc);
	
	//function to draw axes with tick marks on graph
	void DrawAxes(wxDC& dc);

};
