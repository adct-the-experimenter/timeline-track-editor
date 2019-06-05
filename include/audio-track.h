#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H

#include "track.h"
#include "audio-graph.h"

#include "openalsoft-player.h"

#include <functional>   // std::function, std::negate

//Class used to manipulate placement of audio samples in timeline.

class AudioTrack : public Track
{

public:
    AudioTrack(const wxString& title);
    
    virtual void InitTrack(wxWindow* parent, std::vector <int> *timeTickVector);
	
	//function to set bounds for variable to change as well as number of ticks to draw
	virtual void SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick);
	
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
	
    virtual void OnLeftMouseClick(wxMouseEvent& event);
    virtual void OnRightMouseClick(wxCommandEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    
    void SetReferenceToTimeTickVector(std::vector <int> *thisVector);
    std::vector <int> *GetReferenceToTimeTickVector();
    
    void SetTitle(wxString thisTitle);
    wxString GetTitle();
    
    double GetCurrentTime();
    
    void SetReferenceToVarToManipulate(double* thisVar);
    
    virtual void FunctionToCallEveryTimeInTimerLoop();
    
    void SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction); 
    
    void render(wxDC& dc);
    void logic_left_click();
    void logic_right_click();
    
private:

	//source to manipulate
	ALuint* sourceToManipulatePtr;
	
	
	
	double verticalStart; //vertical axis start
	double verticalEnd; //vertical axis end
	double verticalResolution;
	int verticalNumTicks; //number of tick marks in vertical axis
	
	std::vector <double> m_vertical_var_num;
	void InitVerticalAxis();
	std::vector<double> LinearSpacedArray(double a, double b, std::size_t N);
	
    AudioGraph* m_audio_graph;
    
    //2d map to hold output at certain time, for quick reading
    std::unordered_map <double, double> map_time_output;
    
    std::function < void() > func_after_var_change;
	
};

#endif
