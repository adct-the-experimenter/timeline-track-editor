#include "audio-track.h"

AudioTrack::AudioTrack(const wxString& title) : Track(title)
{
	
}

//Audio related functions

void AudioTrack::SetReferenceToSourceToManipulate(ALuint* thisSource){sourceToManipulatePtr = thisSource;}

void AudioTrack::SetReferenceToAudioPlayer(OpenALSoftPlayer* thisPlayer){audioPlayerPtr = thisPlayer;}

//Track related functions

void AudioTrack::FunctionToCallEveryTimeInTimerLoop()
{
	
}


void AudioTrack::SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction)
{
	
} 

void AudioTrack::render(wxDC& dc)
{
	
}

void AudioTrack::logic_left_click()
{
	
}

void AudioTrack::logic_right_click()
{
	
}

void AudioTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	
}

void AudioTrack::SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick)
{
	
}

void InitVerticalAxis()
{
	
}

std::vector<double> LinearSpacedArray(double a, double b, std::size_t N)
{
	
}

void AudioTrack::OnPaint(wxPaintEvent& event)
{
	
}

void AudioTrack::OnScroll(wxScrollEvent& event)
{
	
}

void AudioTrack::OnSize(wxSizeEvent& event)
{
	
}

void AudioTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	
}

void AudioTrack::OnRightMouseClick(wxCommandEvent& event)
{
	
}

void AudioTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable)
{
	
}

void AudioTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector)
{
	
}

std::vector <int> *AudioTrack::GetReferenceToTimeTickVector()
{
	
}

void AudioTrack::SetTitle(wxString thisTitle){}
wxString AudioTrack::GetTitle(){}

double AudioTrack::GetCurrentTime(){}

void AudioTrack::SetReferenceToVarToManipulate(double* thisVar){}


