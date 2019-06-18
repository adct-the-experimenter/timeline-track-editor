#ifndef STEREOAUDIOTRACK_H
#define STEREOAUDIOTRACK_H

#include "track.h"
#include "audio-track.h"

class StereoAudioTrack : public Track
{
public:
	StereoAudioTrack(const wxString& title);
	
	void SetReferenceToSourceToManipulate(ALuint* source);
	void SetReferenceToAudioPlayer(OpenALSoftPlayer* thisPlayer);
	
	AudioTrack* GetReferenceToLeftChannelTrack();
	AudioTrack* GetReferenceToRightChannelTrack();
	
	//Audio Track related functions
	
	
	//Track related functions
	virtual void InitTrack(wxWindow* parent, std::vector <int> *timeTickVector);
	
	//function to set bounds for variable to change as well as number of ticks to draw
	virtual void SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick);
	
	
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnScroll(wxScrollEvent& event);
	virtual void OnSize(wxSizeEvent& event);
	void OnLeftMouseClick(wxMouseEvent& event);
    void OnRightMouseClick(wxCommandEvent& event);
    
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
    
    void SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction); 
    
    void render(wxDC& dc);
    void logic_left_click();
    void logic_right_click();
	
private:
	//object to hold audio data for streaming
	AudioStreamContainer audio_data_stream;
	
	//Hold data for left channel and right channel
	std::vector <double> audio_data_input_copy;
	
	SF_INFO input_sfinfo;
	
	AudioTrack* m_left_channel_track;
	AudioTrack* m_right_channel_track;
	
	ALuint* sourceToManipulatePtr;
	OpenALSoftPlayer* audioPlayerPtr;
	
	double verticalStart; //vertical axis start
	double verticalEnd; //vertical axis end
	double verticalResolution;
	int verticalNumTicks; //number of tick marks in vertical axis
	
	std::function < void() > func_after_var_change;
	
	wxButton* browseButton;
    void OnBrowse(wxCommandEvent& event);
    
    std::string inputSoundFilePath;
    std::string streamSoundFilePath;
    
};

#endif