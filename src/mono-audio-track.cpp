#include "mono-audio-track.h"

MonoAudioTrack::MonoAudioTrack(const wxString& title) : Track(title)
{
	sourceToManipulatePtr = nullptr;
	audioPlayerPtr = nullptr;
	
	//initialize audio tracks
	m_channel_track = new AudioTrack("Left Channel");
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(MonoAudioTrack::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(MonoAudioTrack::OnSize));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MonoAudioTrack::OnLeftMouseClick));
	Connect(wxEVT_CONTEXT_MENU, wxCommandEventHandler(MonoAudioTrack::OnRightMouseClick));
	
	inputSoundFilePath = "";
	streamSoundFilePath = "../resources/stream.wav";
	
}

void MonoAudioTrack::SetReferenceToSourceToManipulate(ALuint* source){sourceToManipulatePtr = source;}
void MonoAudioTrack::SetReferenceToAudioPlayer(OpenALSoftPlayer* thisPlayer){audioPlayerPtr = thisPlayer;}

AudioTrack* MonoAudioTrack::GetReferenceToChannelTrack(){return m_channel_track;}

//Track related functions

void MonoAudioTrack::FunctionToCallInPlayState()
{
	if(m_channel_track != nullptr)
	{
		m_channel_track->FunctionToCallInPlayState();
	}
}

void MonoAudioTrack::FunctionToCallInPauseState(){}
void MonoAudioTrack::FunctionToCallInRewindState(){}
void MonoAudioTrack::FunctionToCallInFastForwardState(){}
void MonoAudioTrack::FunctionToCallInNullState(){}
    
void MonoAudioTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}
void MonoAudioTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){Track::SetReferenceToTimeTickVector(thisVector);}

std::vector <int> *MonoAudioTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

void MonoAudioTrack::SetTitle(wxString thisTitle){Track::SetTitle(thisTitle);}
wxString MonoAudioTrack::GetTitle(){return Track::GetTitle();}

void MonoAudioTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	
	browseButton = new wxButton(parent, wxID_ANY, wxT("Browse"), wxPoint(10,20), wxSize(70, 30) );
	browseButton->Bind(wxEVT_BUTTON, &MonoAudioTrack::OnBrowse,this);
	
	Track::SetReferenceToTimeTickVector(timeTickVector);
}

//function to set bounds for variable to change as well as number of ticks to draw
void MonoAudioTrack::SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick)
{
	verticalStart = start;
	verticalEnd = end;
	verticalNumTicks = numTick;
	verticalResolution = resolution;
	
	
	//setup tick marks
	if(m_channel_track != nullptr )
	{
		m_channel_track->SetupAxisForVariable(verticalStart,verticalEnd,verticalResolution,verticalNumTicks);
	}
	
}

void MonoAudioTrack::OnBrowse(wxCommandEvent& event)
{
	if(audio_data_stream.GetSize() == 0)
	{
		wxFileDialog fileDlg(this, _("Choose the WAV file"), wxEmptyString, wxEmptyString, _("WAV file|*.wav|All files|*.*"));
		if (fileDlg.ShowModal() == wxID_OK)
		{
			wxString path = fileDlg.GetPath();
			//use this path in your app
			inputSoundFilePath = std::string(path.mb_str());
			
			std::cout << "Input Sound file path:" << inputSoundFilePath << std::endl;
			
			std::cout << "Stream sound file path: " << streamSoundFilePath << std::endl;
			
			//create a copy of file to reference for editing
			
			//open file to play during streaming
			audioPlayerPtr->OpenPlayerFile(streamSoundFilePath.c_str());
			 
		} 
	}
	  
}
	
void MonoAudioTrack::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void MonoAudioTrack::OnScroll(wxScrollEvent& event)
{
	//std::cout << "Scroll called! \n";
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}


void MonoAudioTrack::OnPaint(wxPaintEvent& event)
{
	//std::cout << "Current Time in Track:" << *current_time_pos_pointer << std::endl;
	wxPaintDC dc(this);
	
	MonoAudioTrack::render(dc);
}

void MonoAudioTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	
}

void MonoAudioTrack::OnRightMouseClick(wxCommandEvent& event)
{
	
}

double MonoAudioTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void MonoAudioTrack::SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction)
{
	func_after_var_change = thisFunction;
} 
    
void MonoAudioTrack::render(wxDC& dc){}
void MonoAudioTrack::logic_left_click(){}
void MonoAudioTrack::logic_right_click(){}

