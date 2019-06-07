#include "timeline-frame.h"

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{		
	//make horizontal box to put names in
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	
	timelineWindowPtr = new TimelineWindow(this);
	
	wxBoxSizer *hboxTimeline = new wxBoxSizer(wxHORIZONTAL);
	hboxTimeline->Add(timelineWindowPtr, 1, wxRIGHT | wxEXPAND, 0);
	
	//initialize playback controls
	controls = new PlaybackControls(this);
	controls->SetReferenceToTimelineWindow(timelineWindowPtr);
	
	 //create Playback timer object to call playback controls RunPlaybackState() periodically
	timer = new PlaybackTimer(controls);
	
	wxBoxSizer *hboxPlayback = new wxBoxSizer(wxHORIZONTAL);
	hboxPlayback->Add(controls);
	
	vbox->Add(hboxPlayback);
	vbox->Add(hboxTimeline);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT*2);
	
	//Not using SetSizer and Fit because that messes up the scrolling
	SetSizer(vbox);
	Center();
	
	Show();
	timer->start();
}

TimelineFrame::~TimelineFrame()
{
	if(controls != nullptr){delete controls;}
	if(timer != nullptr){delete timer;}
}

TimelineWindow* TimelineFrame::GetTimelineWindow(){return timelineWindowPtr;}

void TimelineFrame::AddTrack(Track* thisTrack, int& space)
{
	TimelineFrame::GetTimelineWindow()->AddTrack(thisTrack,space);
}

void TimelineFrame::AddTrackFunctionToCallInTimerLoopPlayState(Track* thisTrack)
{
	std::function< void() > func = std::bind(&Track::FunctionToCallInPlayState, thisTrack);
	timer->AddFunctionToTimerLoopPlayState(func );
}

void TimelineFrame::AddTrackFunctionToCallInTimerLoopPauseState(Track* thisTrack)
{
	std::function< void() > func = std::bind(&Track::FunctionToCallInPauseState, thisTrack);
	timer->AddFunctionToTimerLoopPauseState(func );
}

void TimelineFrame::AddTrackFunctionToCallInTimerLoopRewindState(Track* thisTrack)
{
	std::function< void() > func = std::bind(&Track::FunctionToCallInRewindState, thisTrack);
	timer->AddFunctionToTimerLoopRewindState(func );
}

void TimelineFrame::AddTrackFunctionToCallInTimerLoopFastForwardState(Track* thisTrack)
{
	std::function< void() > func = std::bind(&Track::FunctionToCallInFastForwardState, thisTrack);
	timer->AddFunctionToTimerLoopFastForwardState(func );
}

void TimelineFrame::AddTrackFunctionToCallInTimerLoopNullState(Track* thisTrack)
{
	std::function< void() > func = std::bind(&Track::FunctionToCallInNullState, thisTrack);
	timer->AddFunctionToTimerLoopNullState(func );
}

void TimelineFrame::AddSpacerBlock(int space)
{
	TimelineFrame::GetTimelineWindow()->AddSpacerBlock(space);
}

void TimelineFrame::AddText(wxString thisText, wxPoint thisPoint)
{
	TimelineFrame::GetTimelineWindow()->AddText(thisText,thisPoint);
}

void TimelineFrame::OnClose(wxCloseEvent& evt)
{
	timer->Stop();
	evt.Skip();
}

BEGIN_EVENT_TABLE(TimelineFrame, wxFrame)
EVT_CLOSE(TimelineFrame::OnClose)
END_EVENT_TABLE()
