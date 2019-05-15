// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "timeline-ruler.h"

//override wxApp to initialize program 
class MyApp: public wxApp
{
public:
    virtual bool OnInit(); //initialize program
};

//override wxFrame to make new custom window
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

//unique identifier to use to react to menu command
enum
{
    ID_Hello = 1
};
