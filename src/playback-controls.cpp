#include "playback-controls.h"

PlaybackControls::PlaybackControls(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	//make horizontal box to put buttons in
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	//initialize buttons
	m_play_button = new wxButton(this, ID_PLAY_BUTTON_HIT, wxT("Play"));;
    m_pause_button = new wxButton(this, wxID_NEW, wxT("Pause"));;
    m_stop_button = new wxButton(this, wxID_NEW, wxT("Stop"));;
    m_rewind_button = new wxButton(this, wxID_NEW, wxT("Rewind"));;
    m_fast_forward_button = new wxButton(this, wxID_NEW, wxT("Fast Forward"));;
    
    m_play_button->Bind(wxEVT_BUTTON,&PlaybackControls::Play,this);
    m_pause_button->Bind(wxEVT_BUTTON,&PlaybackControls::Pause,this);
    m_stop_button->Bind(wxEVT_BUTTON,&PlaybackControls::Stop,this);
    m_rewind_button->Bind(wxEVT_BUTTON,&PlaybackControls::Rewind,this);
    m_fast_forward_button->Bind(wxEVT_BUTTON,&PlaybackControls::FastForward,this);
    
    hbox->Add(m_play_button, 0,  wxALL, 0);
    hbox->Add(m_pause_button, 0,  wxALL, 0);
    hbox->Add(m_stop_button, 0,  wxALL, 0);
    hbox->Add(m_rewind_button, 0,  wxALL, 0);
    hbox->Add(m_fast_forward_button, 0, wxALL, 0);
    
    SetSizerAndFit(hbox);
    
	timelineWindowPtr = nullptr;
}

void PlaybackControls::RunPlaybackState()
{
	switch (current_state)
	{
		case STATE_NULL:{ break;}
		case STATE_PLAY:
		{
			if(timelineWindowPtr != nullptr)
			{
				//increment current time position until end, then set state to null
				double newTime = timelineWindowPtr->GetCurrentTimePosition() + 0.1;
				timelineWindowPtr->SetCurrentTimePosition(newTime);
			} 
			break;
		}
		case STATE_PAUSE:
		{
			if(timelineWindowPtr != nullptr)
			{	
				//save current time position
				
			}
			
			break;
		}
		case STATE_REWIND:
		{
			if(timelineWindowPtr != nullptr)
			{
				//decrement current time position until beginning, then set state to null
				double newTime = timelineWindowPtr->GetCurrentTimePosition() - 0.1;
				timelineWindowPtr->SetCurrentTimePosition(newTime);
			}
			break;
			
		}
		case STATE_FAST_FORWARD:
		{
			if(timelineWindowPtr != nullptr)
			{	
				//increment current time position until end, then set state to null
				//faster than play
				double newTime = timelineWindowPtr->GetCurrentTimePosition() + 0.5;
				timelineWindowPtr->SetCurrentTimePosition(newTime);
			}
			break;
		}
	};
}

void PlaybackControls::Play(wxCommandEvent& event)
{
	current_state = STATE_PLAY;
}

void PlaybackControls::Pause(wxCommandEvent& event)
{
	current_state = STATE_PAUSE;
}

void PlaybackControls::Stop(wxCommandEvent& event)
{
	current_state = STATE_NULL;
}

void PlaybackControls::Rewind(wxCommandEvent& event)
{
	current_state = STATE_REWIND;
}

void PlaybackControls::FastForward(wxCommandEvent& event)
{
	current_state = STATE_FAST_FORWARD;
}

void PlaybackControls::SetReferenceToTimelineWindow(TimelineWindow* thisTimeline){timelineWindowPtr = thisTimeline;}

int PlaybackControls::GetCurrentState(){return current_state;}
