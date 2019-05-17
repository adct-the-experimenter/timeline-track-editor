#include "timeline-window.h"

TimelineWindow::TimelineWindow(wxWindow *parent) : wxScrolled<wxWindow>(parent, wxID_ANY)
{

	m_slider_value = 0;
	m_time_num.resize(9);
	m_time_num = { 0, 10, 20, 30, 40, 50, 60, 70, 80 }; //time in seconds
	
	SetScrollRate( 10, 10 );
    SetVirtualSize( TRACK_WIDTH, TRACK_HEIGHT );
    SetBackgroundColour( *wxWHITE );

	int slider_width = TRACK_WIDTH - 50; //width of slider
	slider = new wxSlider(this, ID_SLIDER, 0, SLIDER_START_VALUE, SLIDER_END_VALUE, wxPoint(SLIDER_START_X, 30), wxSize(slider_width, -1), wxSL_HORIZONTAL);
	
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TimelineWindow::OnScroll));  
	Connect(wxEVT_PAINT, wxPaintEventHandler(TimelineWindow::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(TimelineWindow::OnSize));
	
	Center();
}

void TimelineWindow::OnScroll(wxScrollEvent& event)
{
	m_slider_value = slider->GetValue();
	Refresh();
}

void TimelineWindow::OnSize(wxSizeEvent& event)
{
	Refresh();
}

void TimelineWindow::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	DoPrepareDC(dc); //prepare device context for drawing a scrolling image
	
	//Initialize variables for drawing vertical timeline line indicating current position
	wxPen pen(wxColour(212, 212, 212));
	dc.SetPen(pen);
	
	wxBrush brush1(wxColour(197, 108, 0));
	dc.SetBrush(brush1);
	
	int width = TRACK_WIDTH;
	
	//x coordinate of vertical line representing current position in time
	int offset_slider = 20;
	wxCoord x = SLIDER_START_X + offset_slider +( (TRACK_WIDTH / SLIDER_END_VALUE) * (m_slider_value));
	
	dc.DrawRectangle( wxRect(x, 0, 2, VERTICAL_LINE_HEIGHT_TIME) );
	
	
	//initialize variables for timeline ruler
	
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	
	int step = (int) round(width / 10.0);

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= (int)m_time_num.size(); i++ ) 
	{
		dc.DrawLine(i*step, 0, i*step, 8);
		dc.DrawText( wxString::Format(wxT("%ds"), m_time_num[i-1]) , i*step, 8);
	}
}

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{
	new TimelineWindow(this);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT/2);
	
	Show();
}
