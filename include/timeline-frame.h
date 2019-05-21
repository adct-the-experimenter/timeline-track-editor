#ifndef TIMELINE_FRAME_H
#define TIMELINE_FRAME_H

#include "playback-controls.h"
#include "timeline-window.h"

// Frame that contains Timeline scrolling window and playback controls
class TimelineFrame : public wxFrame
{
public:
    TimelineFrame(wxWindow *parent);
    
    TimelineWindow* GetTimelineWindow();
    
private:
	TimelineWindow* timelineWindowPtr;
};

#endif
