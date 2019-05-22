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
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT);
	
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

void TimelineFrame::OnClose(wxCloseEvent& evt)
{
	timer->Stop();
	evt.Skip();
}

BEGIN_EVENT_TABLE(TimelineFrame, wxFrame)
EVT_CLOSE(TimelineFrame::OnClose)
END_EVENT_TABLE()
