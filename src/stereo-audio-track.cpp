#include "stereo-audio-track.h"

StereoAudioTrack::StereoAudioTrack(const wxString& title) : Track(title)
{
	sourceToManipulatePtr = nullptr;
	audioPlayerPtr = nullptr;
	
	//initialize audio tracks
	m_left_channel_track = new AudioTrack("Left Channel");
	m_right_channel_track = new AudioTrack("Right Channel");
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(StereoAudioTrack::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(StereoAudioTrack::OnSize));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(StereoAudioTrack::OnLeftMouseClick));
	Connect(wxEVT_CONTEXT_MENU, wxCommandEventHandler(StereoAudioTrack::OnRightMouseClick));
	
	inputSoundFilePath = "";
	streamSoundFilePath = "../resources/stream.wav";
	
}

void StereoAudioTrack::SetReferenceToSourceToManipulate(ALuint* source){sourceToManipulatePtr = source;}
void StereoAudioTrack::SetReferenceToAudioPlayer(OpenALSoftPlayer* thisPlayer){audioPlayerPtr = thisPlayer;}

AudioTrack* StereoAudioTrack::GetReferenceToLeftChannelTrack(){return m_left_channel_track;}
AudioTrack* StereoAudioTrack::GetReferenceToRightChannelTrack(){return m_right_channel_track;}

//Track related functions

void StereoAudioTrack::FunctionToCallInPlayState()
{
	if(m_left_channel_track != nullptr)
	{
		m_left_channel_track->FunctionToCallInPlayState();
	}
	
	if(m_right_channel_track != nullptr)
	{
		m_right_channel_track->FunctionToCallInPlayState();
	}
}

void StereoAudioTrack::FunctionToCallInPauseState(){}
void StereoAudioTrack::FunctionToCallInRewindState(){}
void StereoAudioTrack::FunctionToCallInFastForwardState(){}
void StereoAudioTrack::FunctionToCallInNullState(){}
    
void StereoAudioTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}
void StereoAudioTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){Track::SetReferenceToTimeTickVector(thisVector);}

std::vector <int> *StereoAudioTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

void StereoAudioTrack::SetTitle(wxString thisTitle){Track::SetTitle(thisTitle);}
wxString StereoAudioTrack::GetTitle(){return Track::GetTitle();}

void StereoAudioTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	
	browseButton = new wxButton(parent, wxID_ANY, wxT("Browse"), wxPoint(10,20), wxSize(70, 30) );
	browseButton->Bind(wxEVT_BUTTON, &StereoAudioTrack::OnBrowse,this);
	
	Track::SetReferenceToTimeTickVector(timeTickVector);
}

//function to set bounds for variable to change as well as number of ticks to draw
void StereoAudioTrack::SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick)
{
	verticalStart = start;
	verticalEnd = end;
	verticalNumTicks = numTick;
	verticalResolution = resolution;
	
	
	//setup tick marks
	if(m_left_channel_track != nullptr && m_right_channel_track != nullptr)
	{
		m_left_channel_track->SetupAxisForVariable(verticalStart,verticalEnd,verticalResolution,verticalNumTicks);
		m_right_channel_track->SetupAxisForVariable(verticalStart,verticalEnd,verticalResolution,verticalNumTicks);
	}
	
}

void StereoAudioTrack::OnBrowse(wxCommandEvent& event)
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
			
			int channels = m_left_channel_track->GetNumberOfChannelsInAudioFile(inputSoundFilePath,input_sfinfo);
			std::cout << "channels:" << channels << std::endl;
			//create a copy of file to reference for editing
			//also put data into stream
			m_left_channel_track->ReadAndCopyDataFromInputFile(&audio_data_input_copy,inputSoundFilePath,input_sfinfo);
			m_left_channel_track->CopyInputDataIntoAudioDataStream(&audio_data_input_copy,&audio_data_stream,streamSoundFilePath,input_sfinfo);
			
			if(channels == 1)
			{
				//graph all data in channel to one graph
				m_left_channel_track->PlotOneChannelStreamAudioDataToGraph(&audio_data_stream,input_sfinfo);
			}
			else if(channels == 2)
			{	
				//plot left channel data to one graph 
				m_left_channel_track->PlotLeftChannelStreamAudioDataToGraph(&audio_data_stream,input_sfinfo);
				//plot right channel data to other graph
				m_right_channel_track->PlotRightChannelStreamAudioDataToGraph(&audio_data_stream,input_sfinfo);
				
			}
			
			//open file to play during streaming
			//audioPlayerPtr->OpenPlayerFile(streamSoundFilePath.c_str());
			 
		} 
	}
	  
}
	
void StereoAudioTrack::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void StereoAudioTrack::OnScroll(wxScrollEvent& event)
{
	//std::cout << "Scroll called! \n";
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}


void StereoAudioTrack::OnPaint(wxPaintEvent& event)
{
	//std::cout << "Current Time in Track:" << *current_time_pos_pointer << std::endl;
	wxPaintDC dc(this);
	
	StereoAudioTrack::render(dc);
}

void StereoAudioTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	
}

void StereoAudioTrack::OnRightMouseClick(wxCommandEvent& event)
{
	
}

double StereoAudioTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void StereoAudioTrack::SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction)
{
	func_after_var_change = thisFunction;
} 
    
void StereoAudioTrack::render(wxDC& dc)
{
	m_left_channel_track->render(dc);
	m_right_channel_track->render(dc);
}

void StereoAudioTrack::logic_left_click(){}
void StereoAudioTrack::logic_right_click(){}

