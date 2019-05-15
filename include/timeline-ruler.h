#include <wx/wx.h>
#include <wx/slider.h>

class TimelinePanel : public wxPanel
{
public:
    TimelinePanel(wxFrame *parent);

    void OnPaint(wxPaintEvent& event);
    void OnScroll(wxScrollEvent& event);

    wxSlider *slider;
    int fill;

};

class TimelineSlider : public wxFrame
{
public:
    TimelineSlider(const wxString& title);

    TimelinePanel *panel;

};

const int ID_SLIDER = 100;
