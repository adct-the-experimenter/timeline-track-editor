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
    
    template <typename T>
    void render(wxDC& dc, std::vector <T> *verticalAxisVector);
    
    void SetReferenceToTimeTickVector(std::vector <int> *thisVector); 

private:

	std::vector <int> *timeTickVectorPtr;

	std::vector <wxPoint> graph_points; //holds points drawn on graph
	
	std::unordered_map <double, std::vector<wxPoint>::iterator> map_time; //dictionary to keep track of which time values are occupied
	
	//function to place point on mouse event
	void PlacePointByMouse();
	
	//function to draw graph_points on graph
	void DrawCurrentPointsOnGraph(wxDC& dc);
	
	//functions to draw axes 
	
	void DrawHorizontalAxis(wxDC& dc);
	template <typename T>
	void DrawVerticalAxis(wxDC& dc,std::vector <T> *verticalAxisVector);
};
