#include "timeline-window.h"


TimelineFrame::TimelineFrame(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Timeline Frame")
{
	new TimelineWindow(this);
	
	// ensure that we have scrollbars initially
	SetClientSize(TRACK_WIDTH/2, TRACK_HEIGHT/2);
	
	Show();
}

TimelineWindow::TimelineWindow(wxWindow *parent) : wxScrolled<wxWindow>(parent, wxID_ANY)
{
	
	SetScrollRate( 10, 10 ); //how many pixels to increment when scrolling
    SetVirtualSize( TRACK_WIDTH, TRACK_HEIGHT ); //actual size of what will be scrolled
    SetBackgroundColour( *wxWHITE );

	
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(TimelineWindow::OnScroll));  
	Connect(wxEVT_PAINT, wxPaintEventHandler(TimelineWindow::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(TimelineWindow::OnSize));
	
	TimelineWindow::InitTimeline();
	
	//make horizontal box to put names in
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	
	//add slider to box
	hbox->Add(m_slider, 0, wxEXPAND | wxALL, slider_start_x_pos);
	
	SetSizerAndFit(hbox);
	Center();
}

void TimelineWindow::InitTimeline()
{
	m_slider_value = 0;
	
	//intialize m_time_num
	TimelineWindow::InitTimeVector();
	
	slider_start_x_pos = TRACK_WIDTH / (TIME_TICK_NUM - 1);
	
	m_slider = new wxSlider(this, ID_SLIDER, 0, 0, TRACK_WIDTH, wxPoint(slider_start_x_pos, 30), wxSize(TRACK_WIDTH, -1), wxSL_HORIZONTAL);
	
}

void TimelineWindow::InitTimeVector()
{
	//get linearly spaced vector of doubles
	std::vector <double> thisVector = TimelineWindow::LinearSpacedArray(TIME_START_VALUE,TIME_END_VALUE,TIME_TICK_NUM);
	
	for(size_t i=0; i < thisVector.size(); ++i)
	{
		m_time_num.push_back((int)thisVector[i]);
	}
}

std::vector<double> TimelineWindow::LinearSpacedArray(double a, double b, std::size_t N)
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


void TimelineWindow::OnScroll(wxScrollEvent& event)
{
	m_slider_value = m_slider->GetValue();
	Refresh();
	
	FitInside();
}

void TimelineWindow::OnSize(wxSizeEvent& event)
{
	Refresh(); //for wxDc onPaint stuff
	
	FitInside();
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
	
	
	
	//x coordinate of vertical line representing current position in time
	wxCoord x = m_slider_value + slider_start_x_pos;
	
	dc.DrawRectangle( wxRect(x, 0, 2, VERTICAL_LINE_HEIGHT_TIME) );
	
	
	//initialize variables for timeline ruler
	
	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL, false, wxT("Courier 10 Pitch"));
	dc.SetFont(font);
	
	int step = (int) round( TRACK_WIDTH / (TIME_TICK_NUM-1) );

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	
	for ( int i=1; i <= (int)m_time_num.size(); i++ ) 
	{
		dc.DrawLine(i*step, 1, i*step, 10);
		dc.DrawText( wxString::Format( wxT("%ds"), m_time_num[i-1] ) , i*step, 10);
	}
}

