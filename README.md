# Timeline Track Editor
This is a general GUI template that has a timeline and track editor for anyone to use to get started on their project.
A timeline in the GUI of an application is something that many people have used and needed, 
but there was not free open-source code available that was easy to copy and implement.

This project aims to provide an easy-to-integrate timeline track editor that is not application specific.

#Audio track is an experimental feature that is not stable nor complete at the moment.

# Required Libraries

wxwidgets https://www.wxwidgets.org/
libsndfile https://github.com/erikd/libsndfile/

# How to Install

1. Install the required libraries.
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
		
		//add block of space between timeline and track
		int spaceBlockSize = 100;
		timeFrame->AddSpacerBlock(spaceBlockSize);
		
		//add text to the timeline window before track to indicate what variable the track manipulates
		wxBoxSizer* hboxText = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText *text = new wxStaticText(timeFrame->GetTimelineWindow(), wxID_ANY, wxT("Track for someVarToChange"),wxDefaultPosition );
		hboxText->Add(text);
		timeFrame->AddBoxSizer(hboxText);

		//set function to call after variable to manipulate has changed
		//optional
		track1->SetFunctionToCallAfterVariableChange(FunctionForSomeVarAfterChange);
		
		//add track to time frame
		timeFrame->AddTrack(track1,space);
		
		
		//FunctionToCallInXState can be changed to do whatever you want. Functions must be void and take in no parameters.
		//Can add members to DoubleTrack and reference them to get around no parameters or make own class with custom members.

		//makes DoubleTrack::FunctionToCallInPlayState() be called during play
		timeFrame->AddTrackFunctionToCallInTimerLoopPlayState(track1); 
		//makes DoubleTrack::FunctionToCallInPauseState() be called during pause
		timeFrame->AddTrackFunctionToCallInTimerLoopPauseState(track1); 
		//makes DoubleTrack::FunctionToCallInRewindState() be called during rewind
		timeFrame->AddTrackFunctionToCallInTimerLoopRewindState(track1); 
		//makes DoubleTrack::FunctionToCallInFastForwardState() be called during fast forward
		timeFrame->AddTrackFunctionToCallInTimerLoopFastForwardState(track1); 
		//makes DoubleTrack::FunctionToCallInNullState() be called when nothing is happening after stop button pressed
		timeFrame->AddTrackFunctionToCallInTimerLoopNullState(track1); 

		//Initialize Audio Track

		//Initialize OpenAL Soft
		
		audioPlayer = new OpenALSoftPlayer();
		
		if(!audioPlayer->InitOpenALSoft(audioDevice,alContext))
		{
			std::cout << "Unable to make audio track because OpenAL SOft could not be initialized! \n";
		}
		else
		{
			audioPlayer->SetReferenceToAudioContext(alContext);
			audioPlayer->SetReferenceToAudioDevice(audioDevice);
			
			audioPlayer->InitBuffersForStreaming();
			
			AudioTrack* track2 = new AudioTrack("Audio");
		
			start = 0.0f; //lowest value
			end = 1.0f; //highest value
			numTicks = 11; //number of ticks between lowest value and highest value including zero
			resolution = 0.1; //the fineness of how much variable can be incremented/decremented by

			//setup bounds for vertical axis
			track2->SetupAxisForVariable(start,end,resolution,numTicks);
			
			//add track to time frame
			timeFrame->AddTrack(track2,space);
			
			track2->Show();
		}
	}

	
For further customization use DoubleTrack and/or AudioTrack class as a template to create a new class to handle specific class types.

# To place points on graph in DoubleTrack
Left click on graph in track to place a point in track. 
Right Click on point in graph in track to remove a point from the graph.
