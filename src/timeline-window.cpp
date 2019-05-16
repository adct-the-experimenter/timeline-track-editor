#include "timeline-window.h"

TimelineWindow::TimelineWindow(wxWindow *parent) : wxScrolled<wxWindow>(parent, wxID_ANY)
{
	
	fill = 0;
	
	SetScrollRate( 10, 10 );
    SetVirtualSize( TRACK_WIDTH, TRACK_HEIGHT );
    SetBackgroundColour( *wxWHITE );

	int slider_width = TRACK_WIDTH - 50; //width of slider
	slider = new wxSlider(this, ID_SLIDER, 0, 0, 140, wxPoint(SLIDER_START_X, 30), wxSize(slider_width, -1), wxSL_HORIZONTAL);
	
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TimelineWindow::OnScroll));  
	Connect(wxEVT_PAINT, wxPaintEventHandler(TimelineWindow::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(TimelineWindow::OnSize));

	Center();

}

void TimelineWindow::OnScroll(wxScrollEvent& event)
{
	fill = slider->GetValue();
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
	
	wxSize size = GetSize();
	int width = TRACK_WIDTH;
	
	int x_units,y_units;
	this->GetScrollPixelsPerUnit(&x_units,&y_units);
	
	//x coordinate of vertical line representing current position in time
	wxCoord x = SLIDER_START_X + 18 + (fill * (0.5*x_units + 0.05));
	
	dc.DrawRectangle( wxRect(x, 0, 2, 200) );
	
	
	//initialize variables for timeline ruler
	int num[] = { 75, 150, 225, 300, 375, 450, 525, 600, 675 };// numbers to display on ruler
	int asize = sizeof(num)/sizeof(num[1]);
	
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	
	int step = (int) round(width / 10.0);

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= asize; i++ ) 
	{
		dc.DrawLine(i*step, 0, i*step, 6);
		wxSize size = dc.GetTextExtent(wxString::Format(wxT("%d"), num[i-1]));
		dc.DrawText( wxString::Format(wxT("%d"), num[i-1]) , i*step, 8);
	}
}

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{
	new TimelineWindow(this);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT/2);
	
	Show();
}
