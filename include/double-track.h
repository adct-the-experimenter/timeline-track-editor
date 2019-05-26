#ifndef DOUBLE_TRACK_H
#define DOUBLE_TRACK_H

#include "track.h"
#include "editor-graph.h"

class DoubleTrack : public Track
{

public:
    DoubleTrack(const wxString& title);
    
    virtual void InitTrack(wxWindow* parent, std::vector <int> *timeTickVector);
	
	//function to set bounds for variable to change as well as number of ticks to draw
	virtual void SetBoundsForVariable(double& start, double& end, int& numTick);
	
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
	
    virtual void OnLeftMouseClick(wxMouseEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    
    void SetReferenceToTimeTickVector(std::vector <int> *thisVector);
    std::vector <int> *GetReferenceToTimeTickVector();
    
    double GetCurrentTime();
    
    void SetReferenceToVarToManipulate(double* thisVar);
    
private:

	double* varToManipulatePtr;
	
	double verticalStart; //vertical axis start
	double verticalEnd; //vertical axis end
	int verticalNumTicks; //number of tick marks in vertical axis
	
	std::vector <double> m_vertical_var_num;
	void InitVerticalAxis();
	std::vector<double> LinearSpacedArray(double a, double b, std::size_t N);
	
    EditorGraph* graphEditor;
    
};

#endif
