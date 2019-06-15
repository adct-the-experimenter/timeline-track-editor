#include "audio-track.h"

/*
 * Code adapted from sfprocess.c on libsndfile github
** Copyright (C) 2001-2013 Erik de Castro Lopo <erikd@mega-nerd.com>
**
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**
**	 * Redistributions of source code must retain the above copyright
**	   notice, this list of conditions and the following disclaimer.
**	 * Redistributions in binary form must reproduce the above copyright
**	   notice, this list of conditions and the following disclaimer in
**	   the documentation and/or other materials provided with the
**	   distribution.
**	 * Neither the author nor the names of any contributors may be used
**	   to endorse or promote products derived from this software without
**	   specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
** ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
	if(audio_data_stream.GetSize() == 0)
	{
		wxFileDialog fileDlg(this, _("Choose the WAV file"), wxEmptyString, wxEmptyString, _("WAV file|*.wav|All files|*.*"));
		if (fileDlg.ShowModal() == wxID_OK)
		{
			wxString path = fileDlg.GetPath();
			//use this path in your app
			inputSoundFilePath = std::string(path.mb_str());
			
			std::cout << "Input Sound file path:" << inputSoundFilePath << std::endl;
			streamSoundFilePath = "../resources/stream.wav";
			std::cout << "Stream sound file path: " << streamSoundFilePath << std::endl;
			
			//create a copy of file to reference for editing
			AudioTrack::ReadAndCopyDataFromInputFile();
			
			AudioTrack::PlotStreamAudioDataToGraph();
			
			//open file to play during streaming
			audioPlayerPtr->OpenPlayerFile(streamSoundFilePath.c_str());
			 
		} 
		
	}
	  
}

void AudioTrack::ReadAndCopyDataFromInputFile()
{
	//Read data from file
	if (! (inputFile = sf_open (inputSoundFilePath.c_str(), SFM_READ, &input_sfinfo)))
	{	
		// Open failed, so print an error message.
		std::cout << "Not able to open input file " <<  inputSoundFilePath << std::endl;
		/* Print the error message from libsndfile. */
		puts (sf_strerror (NULL)) ;
		return;
	} 
		
	if (input_sfinfo.channels > MAX_CHANNELS)
	{
		std::cout << "Not able to process more than" <<  MAX_CHANNELS << "channels.\n";
		return;
	}
	std::cout << "Successfully loaded " << inputSoundFilePath << " saving data..." << std::endl;
	
	//read input data
	std::vector<double> read_buf(BUFFER_LEN);
	size_t read_size = 0;
	while( (read_size = sf_read_double(inputFile, read_buf.data(), read_buf.size()) ) != 0)
	{
		audio_data_input_copy.insert(audio_data_input_copy.end(), read_buf.begin(), read_buf.begin() + read_size);
	}
	
	//copy input audio data references to audio data stream
	audio_data_stream.ResizeAudioStream(audio_data_input_copy.size());
	for(size_t i=0; i < audio_data_stream.GetSize(); i++)
	{
		audio_data_stream.SetPointerToDataAtThisSampleIndex(&audio_data_input_copy[i],i);
	}
	
	double slen;
	//slen = audio_data_track_stream.size() * sizeof(uint16_t); //get size of data in bytes
	slen = audio_data_stream.GetSize() * sizeof(uint16_t);
	
	std::cout << "Size of data in bytes: " << slen << "\n";
	//if sample buffer is null or size of buffer data is zero, notify of error
	if(slen == 0)
	{
		std::string messageString;
		messageString.append("Failed to read audio from file.\n");
		wxMessageBox( messageString );
		return;
	}
	
	double seconds = (1.0 * input_sfinfo.frames) / input_sfinfo.samplerate ;
	std::cout << "Duration of sound:" << seconds << "s. \n";
	
	audio_data_stream.WriteStreamContentsToFile(streamSoundFilePath, input_sfinfo.format, input_sfinfo.channels, input_sfinfo.samplerate,int(BUFFER_LEN));

	/* Close input and stream files. */
	sf_close(inputFile);

	//Plot current audio data in audio data track stream
	AudioTrack::PlotStreamAudioDataToGraph();
	
	std::string messageString;
	messageString.append("Successfully loaded and saved a copy of audio data of");
	messageString.append(inputSoundFilePath);
	wxMessageBox( messageString );
}

void AudioTrack::PlotStreamAudioDataToGraph()
{
	m_audio_graph->PlotStreamAudioDataToGraph(&audio_data_stream,input_sfinfo.samplerate,
										verticalStart, verticalEnd, verticalResolution);
	Refresh();
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



