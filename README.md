# Timeline Track Editor
This is a general GUI template that has a timeline and track editor for anyone to use to get started on their project.
A timeline in the GUI of an application is something that many people have used and needed, 
but there was not free open-source code available that was easy to copy and implement.

This project aims to provide an easy-to-integrate timeline track editor that is not application specific.

# Required Library

wxwidgets https://www.wxwidgets.org/


# How to Install

1. Install the required library.
2. Clone this repository
3. cd timeline-track-editor
4. mkdir build
5. cd build
6. cmake .. -DwxWidgets_CONFIG_EXECUTABLE=path-to-wxconfig-executable
    
    FreeBSD: path-to-wxconfig-executable = /usr/local/bin/wxgtk3u-3.1-config
    
    Linux: path-to-wxconfig-executable = /usr/bin/wx-config-gtk3
7. make
8. ./timeline-track-editor


# How to Use:

This section is a work in progress. It will be updated as needed.

Set parameters for window and tracks in the parameters.h file. 
Make sure to use make to update executable after editing parameters.

Add a track by initializing it in the main frame of the application and then use timeline window function TimelineWindow::AddTrack.

	MyFrame::MyFrame()
	{
		//Code for custom menus such as file,edit,help, etc. go here
		//...
		
		//Initialize frame that holds timeline
		TimelineFrame *timeFrame = new TimelineFrame(this);
		
		//add a track to frame holding timeline
		Track* track1 = new Track("Variable Track");
		
		int space = 20; //the distance,in pixels, between track and previous item(timeline or previous track)
		timeFrame->GetTimelineWindow()->AddTrack(&track1,space);
		
		//Show timeframe and added track
		timeFrame->Show(true);
		track1->Show(true);
	}
	
