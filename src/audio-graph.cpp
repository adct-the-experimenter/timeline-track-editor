#include "audio-graph.h"

AudioGraph::AudioGraph(wxWindow* parent) : wxPanel(parent)
{
	
}
    
void AudioGraph::mouseDownLeftClick()
{
	
}

void AudioGraph::mouseDownRightClick()
{
	
}

void AudioGraph::render(wxDC& dc, std::vector <double> *verticalAxisVector)
{
	AudioGraph::DrawHorizontalAxis(dc);
}

void AudioGraph::SetReferenceToTimeTickVector(std::vector <int> *thisVector){}


int AudioGraph::GetVerticalGraphValueAtThisTime(double& thisTime,bool& legitValue)
{
	
}


void AudioGraph::DrawCurrentPointsOnGraph(wxDC& dc)
{
	
}

void AudioGraph::DrawHorizontalAxis(wxDC& dc)
{
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	int step = (int) round( TRACK_WIDTH / (TIME_TICK_NUM-1) );
	int offset = TRACK_WIDTH / (TIME_TICK_NUM - 1);
	
	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= (int)timeTickVectorPtr->size(); i++ ) 
	{
		dc.DrawLine(i*step - offset, 1, i*step - offset , 10);
		
		//skip drawing the zero tick maker because it is mixes with text of vertical axis
		if(i != 1)
		{
			dc.DrawText( wxString::Format( wxT("%ds"), (int)timeTickVectorPtr->at(i-1) ) , i*step - offset, 10);
		}
		
	}
}

void AudioGraph::DrawVerticalAxis(wxDC& dc,std::vector <double> *verticalAxisVector)
{
	
}
