#include "stereo-audio-track.h"

StereoAudioTrack::StereoAudioTrack(const wxString& title) : Track(title)
{
	sourceToManipulatePtr = nullptr;
	audioPlayerPtr = nullptr;
	
	m_audio_graph = nullptr;
}

//Track related functions

void FunctionToCallInPlayState(){}
void FunctionToCallInPauseState(){}
void FunctionToCallInRewindState(){}
void FunctionToCallInFastForwardState(){}
void FunctionToCallInNullState(){}
    
void StereoAudioTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}
void StereoAudioTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){Track::SetReferenceToTimeTickVector(thisVector);}

std::vector <int> *StereoAudioTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

void StereoAudioTrack::SetTitle(wxString thisTitle){Track::SetTitle(thisTitle);}
wxString StereoAudioTrack::GetTitle(){return Track::GetTitle();}

void StereoAudioTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	Track::SetReferenceToTimeTickVector(timeTickVector);
	
	m_left_channel_track = new AudioTrack("Left Channel");
	m_right_channel_track = new AudioTrack("Right Channel");
	
	m_left_channel_track->InitTrack(parent,timeTickVector);
	m_right_channel_track->InitTrack(parent,timeTickVector);
}

void StereoAudioTrack::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void StereoAudioTrack::OnScroll(wxScrollEvent& event)
{
	//std::cout << "Scroll called! \n";
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}


void StereoAudioTrack::OnPaint(wxPaintEvent& event)
{
	//std::cout << "Current Time in Track:" << *current_time_pos_pointer << std::endl;
	
}

double StereoAudioTrack::GetCurrentTime(){return Track::GetCurrentTime();}

