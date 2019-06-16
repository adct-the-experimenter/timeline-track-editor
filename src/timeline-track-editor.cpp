#include "timeline-track-editor.h"

//event table to out event commands to functions
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

//implements  main in MyApp(derived from wxApp)
wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
	//make new main window
	//window title: hello world
	//size: wxSize(450, 340)
	//location: wxPoint(50, 50)
    MyFrame *frame = new MyFrame( "The Name of the Application here", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    
    return true;
}



void MyApp::OnIdle(wxIdleEvent &event)
{
    std::cout << "MyApp is Idle." << std::endl;

    event.RequestMore();
    
    
}

//declare variable to change
double someVarToChange;

//declare a function to use if variable changes
void FunctionForSomeVarAfterChange()
{
	std::cout << "someVarToChange:" << someVarToChange << std::endl;
	std::cout << "function for some var change called! Do something now that double-type SomeVarToChange has changed\n";
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	//create file menu item
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    //create help menu item
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    
    //create and  set menu bar with items file and help
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" ); //connect file menu item to file
    menuBar->Append( menuHelp, "&Help" ); //connect help menu item to help
    SetMenuBar( menuBar );
    
    CreateStatusBar();
    SetStatusText( "Welcome to the app!" );
    
    //Code to initialize timeline track editor part of GUI
    
    TimelineFrame *timeFrame = new TimelineFrame(this); 

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
		
		audioPlayer->InitSource(&source);
		
		AudioTrack* track2 = new AudioTrack("Audio");
		track2->SetReferenceToSourceToManipulate(&source);
		track2->SetReferenceToAudioPlayer(audioPlayer);
		
		double start = 0.0f; //lowest value
		double end = 1.0f; //highest value
		int numTicks = 11; //number of ticks between lowest value and highest value including zero
		double resolution = 0.1; //the fineness of how much variable can be incremented/decremented by

		//setup bounds for vertical axis
		track2->SetupAxisForVariable(start,end,resolution,numTicks);
		
		int space = 20;
		//add track to time frame
		timeFrame->AddTrack(track2,space);
		timeFrame->AddTrackFunctionToCallInTimerLoopPlayState(track2);
		track2->Show();
	}
	
	
	
//Show Tracks and Time Frame

	timeFrame->Show(true); //show the timeframe
		
}




void MyFrame::OnExit(wxCommandEvent& event)
{
	audioPlayer->CloseOpenALSoft(audioDevice,alContext);
    Close( true ); //close window
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	//show message box with ok icon, 
	//window title:about hello world
	//message: This is a wxWidgets Helo world sample
    wxMessageBox( "This is a sample to use for your project",
                  "About the Project", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	//show message
    wxLogMessage("Hello world!");
}


