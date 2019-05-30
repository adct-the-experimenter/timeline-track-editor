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

IMPORTANT NOTE: TIME_RESOLUTION must be 500 ms or larger for best results.

Add a track by initializing it in the main frame of the application and then use timeline window function TimelineWindow::AddTrack.

	//declare variable to change
	double someVarToChange; 
	
	//declare a function to use if variable changes
	void FunctionForSomeVarAfterChange()
	{
		std::cout << "someVarToChange:" << someVarToChange << std::endl;
		std::cout << "function for some var change called! Do something now that double-type SomeVarToChange has changed\n";
	}
	
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
		double resolution = 1; //the fineness of how much variable can be incremented/decremented by

		track1->SetupAxisForVariable(start,end,resolution,numTicks); //setup bounds for vertical axis

		//Put in the variable to change with the timeline.
		// IMPORTANT NOTE: someVarToChange must be declared outside of scope of MyFrame constructor 
		//and not go out of scope or else a segmentation fault happens
		track1->SetReferenceToVarToManipulate(&someVarToChange); 

		//set function to call after variable to manipulate has changed
		//optional
		track1->SetFunctionToCallAfterVariableChange(FunctionForSomeVarAfterChange);
		
		//add track to time frame
		timeFrame->AddTrack(track1,space);
		//add function to call during playback to timeframe 
		//so that someVarToChange can be changed according to Track FunctionToCallEveryTimeInTimerLoop
		timeFrame->AddTrackFunctionToCallInTimerLoop(track1);

		track1->Show(); //show the track
		timeFrame->Show(true); //show the timeframe
	}

	
For further customization use DoubleTrack class as a template to create a new class to handle specific class types.

# To place points on graph 
Left click on graph in track to place a point in track. 
Right Click on point in graph in track to remove a point from the graph.
