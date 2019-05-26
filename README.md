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
		
		//Code to initialize timeline track editor part of GUI
		
		TimelineFrame *timeFrame = new TimelineFrame(this);
    
		int space = 20; //the distance,in pixels, between track and previous item(timeline or previous track)
		DoubleTrack* track1 = new DoubleTrack("Variable Track");
		
		double start = -10.0f; //lowest value
		double end = 10.0f; //highest value
		int numTicks = 11; //number of ticks between lowest value and highest value including zero
		
		track1->SetBoundsForVariable(start,end,numTicks); //setup bounds for vertical axis
		
		timeFrame->GetTimelineWindow()->AddTrack(track1,space);
		
		track1->Show();
		timeFrame->Show(true);
	}
	
