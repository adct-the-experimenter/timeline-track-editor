#include "timeline-window.h"

TimelineWindow::TimelineWindow(wxWindow *parent) : wxScrolled<wxWindow>(parent, wxID_ANY)
{
	
	fill = 0;
	
	SetScrollRate( 10, 10 );
    SetVirtualSize( WIDTH, HEIGHT );
    SetBackgroundColour( *wxWHITE );

	
	slider = new wxSlider(this, ID_SLIDER, 0, 0, 140, wxPoint(50, 30), wxSize(200, -1), wxSL_HORIZONTAL);
	
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
	//resize slider width with window resize
	wxSize size = GetSize();
	int width = size.GetWidth() - 50;
	slider->SetSize(width,-1);
	
	Refresh();
}

void TimelineWindow::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	//Initialize variables for drawing vertical timeline line indicating current position
	wxPen pen(wxColour(212, 212, 212));
	dc.SetPen(pen);
	
	wxBrush brush1(wxColour(197, 108, 0));
	dc.SetBrush(brush1);
	
	wxSize size = GetSize();
	int width = size.GetWidth();

	wxCoord x = fill + (width / 10);

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
		dc.DrawText(wxString::Format(wxT("%d"), num[i-1]), i*step - size.GetWidth()/2, 8);
	}
}

TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "MySimpleCanvas")
{
	new TimelineWindow(this);
	
	// ensure that we have scrollbars initially
	SetClientSize(WIDTH/2, HEIGHT/2);

	Show();
}
