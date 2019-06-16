#ifndef STEREOAUDIOTRACK_H
#define STEREOAUDIOTRACK_H

#include "track.h"
#include "audio-track.h"

class StereoAudioTrack : public Track
{
public:
	StereoAudioTrack();
	
	void SetReferenceToSourceToManipulate(ALuint* source);
	
	//Track related functions
	virtual void InitTrack(wxWindow* parent, std::vector <int> *timeTickVector);

    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
    
    void SetReferenceToCurrentTimeVariable(double* thisTimeVariable);
    void SetReferenceToTimeTickVector(std::vector <int> *thisVector);
    
	void SetTitle(wxString thisTitle);
    wxString GetTitle();
    
    std::vector <int> *GetReferenceToTimeTickVector();
    
    double GetCurrentTime();
    
    //function to call in timer loop, variable to manipulate gets changed here
    virtual void FunctionToCallInPlayState();
    virtual void FunctionToCallInPauseState();
    virtual void FunctionToCallInRewindState();
    virtual void FunctionToCallInFastForwardState();
    virtual void FunctionToCallInNullState();
	
private:
	AudioTrack* m_left_channel_track;
	AudioTrack* m_right_channel_track;
	
	ALuint* sourceToManipulatePtr;
};

#endif
