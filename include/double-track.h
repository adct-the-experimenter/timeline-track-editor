#ifndef DOUBLE_TRACK_H
#define DOUBLE_TRACK_H

#include "track.h"
#include "editor-graph.h"

class DoubleTrack : public Track
{

public:
    DoubleTrack(const wxString& title);
    
    virtual void InitTrack(wxWindow* parent);

    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    
    double GetCurrentTime();
    
    void SetReferenceToVarToManipulate(double* thisVar);
    
private:

	double* varToManipulatePtr;
    EditorGraph* graphEditor;
    
};

#endif
