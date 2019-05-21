#include "timeline-frame.h"

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{
	
	timelineWindowPtr = new TimelineWindow(this);
	
	PlaybackControls* controls = new PlaybackControls(parent);
	controls->SetReferenceToTimelineWindow(timelineWindowPtr);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT/2);
	
	Show();
}

TimelineWindow* TimelineFrame::GetTimelineWindow(){return timelineWindowPtr;}
