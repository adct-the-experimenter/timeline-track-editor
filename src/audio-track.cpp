#include "audio-track.h"

AudioTrack::AudioTrack(const wxString& title) : Track(title)
{
	state = PLAYER_NULL;
	sourceToManipulatePtr = nullptr;
	audioPlayerPtr = nullptr;
	
	m_audio_graph = nullptr;
}

//Audio related functions

void AudioTrack::SetReferenceToSourceToManipulate(ALuint* thisSource){sourceToManipulatePtr = thisSource;}

void AudioTrack::SetReferenceToAudioPlayer(OpenALSoftPlayer* thisPlayer){audioPlayerPtr = thisPlayer;}

//Track related functions

void al_nssleep(unsigned long nsec)
{
    struct timespec ts, rem;
    ts.tv_sec = nsec / 1000000000ul;
    ts.tv_nsec = nsec % 1000000000ul;
    while(nanosleep(&ts, &rem) == -1 && errno == EINTR){ts = rem;}
}

void AudioTrack::FunctionToCallInPlayState()
{
	if(sourceToManipulatePtr != nullptr && audioPlayerPtr != nullptr)
	{
		switch(state)
		{
			case PLAYER_NULL:
			{
				audioPlayerPtr->StartPlayer(sourceToManipulatePtr); //start player
				state = PLAYER_PLAYING; //switch to player started state
				break;
			}
			case PLAYER_PLAYING:
			{
				audioPlayerPtr->UpdatePlayer(sourceToManipulatePtr);
				al_nssleep(10000000);
				break;
			}
		}
		
	}
}

void AudioTrack::FunctionToCallInPauseState()
{
	if(state != PLAYER_PAUSED)
	{
		if(sourceToManipulatePtr != nullptr && audioPlayerPtr != nullptr)
		{
			audioPlayerPtr->PauseSource(sourceToManipulatePtr);
			state = PLAYER_PAUSED;
		}	
	}
}

void AudioTrack::FunctionToCallInRewindState()
{
	if(sourceToManipulatePtr != nullptr && audioPlayerPtr != nullptr)
	{
		alSourceRewind(*sourceToManipulatePtr);
		state = PLAYER_REWINDING;
	}
}

void AudioTrack::FunctionToCallInFastForwardState()
{
	
}

void AudioTrack::FunctionToCallInNullState()
{
	
}

void AudioTrack::SetFunctionToCallAfterVariableChange(std::function < void() > thisFunction){func_after_var_change = thisFunction;} 

void AudioTrack::render(wxDC& dc)
{
	m_audio_graph->render(dc,&m_vertical_var_num);
}

void AudioTrack::logic_left_click()
{
	
}

void AudioTrack::logic_right_click()
{
	
}

void AudioTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
	Track::InitTrack(parent,timeTickVector);

	browseButton = new wxButton(parent, wxID_ANY, wxT("Browse"), wxPoint(10,350), wxSize(70, 30) );
	browseButton->Bind(wxEVT_BUTTON, &AudioTrack::OnBrowse,this);
	
	//initialize audio graph
	m_audio_graph = new AudioGraph(this);
	m_audio_graph->SetReferenceToTimeTickVector(timeTickVector);
}

void AudioTrack::OnBrowse(wxCommandEvent& event)
{
	wxFileDialog fileDlg(this, _("Choose the WAV file"), wxEmptyString, wxEmptyString, _("WAV file|*.wav|All files|*.*"));
	if (fileDlg.ShowModal() == wxID_OK)
	{
		wxString path = fileDlg.GetPath();
		//use this path in your app
		soundFilePath = std::string(path.mb_str());
		std::cout << "Sound file path:" << soundFilePath << std::endl;
		
		//create a copy of file to reference for editing
		
		//write data to .wav file to play during streaming
		
		//open file to play during streaming
		//audioDevicePtr->OpenPlayerFile(soundFilePath.c_str(); 
	}   
}

void AudioTrack::SetupAxisForVariable(double& start, double& end, double& resolution, int& numTick)
{
	verticalStart = start;
	verticalEnd = end;
	verticalNumTicks = numTick;
	verticalResolution = resolution;
	
	//setup tick marks
	AudioTrack::InitVerticalAxis();
}

void AudioTrack::InitVerticalAxis()
{
	//get linearly spaced vector of doubles
	std::vector <double> thisVector = AudioTrack::LinearSpacedArray(verticalStart,verticalEnd,(size_t)verticalNumTicks);
	
	for(size_t i=0; i < thisVector.size(); ++i)
	{
		m_vertical_var_num.push_back(thisVector[i]);
	}
}

std::vector<double> AudioTrack::LinearSpacedArray(double a, double b, std::size_t N)
{
	// Linear interpolation following MATLAB linspace
	double h = (b - a) / static_cast<double>(N-1);
	std::vector<double> xs(N);
	std::vector<double>::iterator x;
	double val;
	for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) {
		*x = val;
	}
	return xs;
}

void AudioTrack::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	AudioTrack::render(dc);
}

void AudioTrack::OnScroll(wxScrollEvent& event)
{
	Refresh(); //for wxDc onPaint stuff 
	
	FitInside(); //for scroll and sizer
}

void AudioTrack::OnSize(wxSizeEvent& event)
{
	Refresh();

	FitInside();
}

void AudioTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	
}

void AudioTrack::OnRightMouseClick(wxCommandEvent& event)
{
	
}

void AudioTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable){Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);}

void AudioTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector){ Track::SetReferenceToTimeTickVector(thisVector);}

std::vector <int> *AudioTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

void AudioTrack::SetTitle(wxString thisTitle){Track::SetTitle(thisTitle);}

wxString AudioTrack::GetTitle(){return Track::GetTitle();}

double AudioTrack::GetCurrentTime(){return Track::GetCurrentTime();}

void AudioTrack::SetReferenceToVarToManipulate(double* thisVar){}


