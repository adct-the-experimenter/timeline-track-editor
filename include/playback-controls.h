#ifndef PLAYBACK_CONTROLS_H
#define PLAYBACK_CONTROLS_H

#include <wx/wx.h>
#include <wx/button.h>
#include <wx/timer.h>

#include <iostream>
#include <vector>

#include "timeline-window.h"

class PlaybackControls : public wxWindow
{
public:
	PlaybackControls(wxWindow* parent);
	
	void RunPlaybackState();
	int GetCurrentState();
	void SetReferenceToTimelineWindow(TimelineWindow* thisTimeline);
	
private:
	
	TimelineWindow* timelineWindowPtr;
	
	int current_state;
	
	enum 
	{
		STATE_NULL = 0,
		STATE_PLAY,
		STATE_PAUSE,
		STATE_REWIND,
		STATE_FAST_FORWARD,
		ID_PLAY_BUTTON_HIT,
		ID_PAUSE_BUTTON_HIT,
		ID_STOP_BUTTON_HIT,
		ID_FAST_FORWARD_BUTON_HIT,
		ID_REWIND_BUTTON_HIT
	};
	
	wxButton *m_play_button;
    wxButton *m_pause_button;
    wxButton *m_stop_button;
    wxButton *m_rewind_button;
    wxButton *m_fast_forward_button;
    
    void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Stop(wxCommandEvent& event);
	void Rewind(wxCommandEvent& event);
	void FastForward(wxCommandEvent& event);
};

//class to use with mainframe
class PlaybackTimer : public wxTimer
{
	enum
	{
		TIMER_INTERVAL = 100 //when to take action, in milliseconds
	};
public:
    PlaybackTimer(PlaybackControls* controls);
    void Notify(); //action to take periodically after certain amount of time defined
    void start();

private:
	PlaybackControls* m_controls;
};


#endif
