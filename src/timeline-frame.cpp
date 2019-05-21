#include "timeline-frame.h"

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{
	
	timelineWindowPtr = new TimelineWindow(this);
	
	controls = new PlaybackControls(parent);
	controls->SetReferenceToTimelineWindow(timelineWindowPtr);
	timer = new PlaybackTimer(controls);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT/2);
	
	
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
