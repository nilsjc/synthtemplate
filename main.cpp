#include "wx/wx.h"
#include "wx/slider.h"
#include <wx/event.h>
#include "wx/button.h"
#include <iostream>
#include "SynthManager.h"
#include "AudioStream.h"
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void StartAudio();
    void StopAudio();


private:
    softsynth::Manager manager;
    softsynth::Runner runner;
    void OnSlChanged(wxCommandEvent &event);
    void StartStopAudio(wxCommandEvent &event);
    void OnKeyDown(wxKeyEvent& event);
    bool running = false;
    wxStaticText *label10 = new wxStaticText(this, 20010, "0");
    wxSlider* sliders[8]={
        new wxSlider(this,101,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,102,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,103,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,104,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,105,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,106,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,107,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator),
        new wxSlider(this,108,50,1,100,wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL, wxDefaultValidator)
    };
    wxButton* startStopButton = new wxButton(this, 30001, "start audio");
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Related to precalculations in audio engine
    manager.Init();

    // Wxwidgets related stuff
    wxGridSizer *grid = new wxGridSizer(3, 8, 0, 0);

    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MyFrame::OnKeyDown));
    //grid->Bind(wxEVT_CHAR_HOOK, &MyFrame::OnKeyDown, this);

    // bind sliders to function
    for(int x=0; x <8; x++)
    {
        sliders[x]->Bind(wxEVT_SLIDER, &MyFrame::OnSlChanged, this);
    }
    // add sliders to grid
    for(int x=0; x <8; x++)
    {
        grid->Add(sliders[x],1, wxEXPAND | wxALL);
    }

    //bind buttons
    startStopButton->Bind(wxEVT_BUTTON, &MyFrame::StartStopAudio, this);

    grid->Add(new wxStaticText(this, 20001, "freq"));
    grid->Add(new wxStaticText(this, 20002, "vol"));
    grid->Add(new wxStaticText(this, 20003, ""));
    grid->Add(new wxStaticText(this, 20004, ""));
    grid->Add(new wxStaticText(this, 20005, ""));
    grid->Add(new wxStaticText(this, 20006, ""));
    grid->Add(new wxStaticText(this, 20007, ""));
    grid->Add(new wxStaticText(this, 20008, ""));
    grid->Add(startStopButton);
    grid->Add(new wxStaticText(this, 20008, ""));
    grid->Add(label10, 1, wxEXPAND | wxALL);

    this->SetSizer(grid);
    grid->Layout();
}

void MyFrame::StartAudio()
{
    // start reverb engine
    runner.SetManager(&manager);
    //runner.Open();
}
void MyFrame::StartStopAudio(wxCommandEvent &event)
{
    if(running)
    {
        runner.Terminate();
        startStopButton->SetLabel("start audio");
    }else{
        runner.Open();
        startStopButton->SetLabel("stop audio");
    }
    running ^= true;
    event.Skip();
}

void MyFrame::OnKeyDown(wxKeyEvent &event)
{
    int keycode = event.GetKeyCode();
    label10->SetLabel(std::to_string(keycode));
    if (keycode == 'q' || keycode == 'Q')
    {
        // do something
    }
    event.Skip();
}


void MyFrame::OnSlChanged(wxCommandEvent &event)
{
    int slider = event.GetId() - 100;
    int value = sliders[(slider-1)]->GetValue();
    switch (slider)
    {
        case 1:
        {
            int freq = value;//(value)/15.0;
            manager.SetFrequency(freq*2);
            label10->SetLabel(std::to_string(freq));
        }
        break;
        case 2:
        {
            float volF = value/100.0;
            manager.SetSynthVol(volF);
            label10->SetLabel(std::to_string(volF));
        }
            break;
        case 3:
        {}
            break;
        case 4:
        {}
            break;
        case 5:
        {}
            break;
        case 6:
        {}
            break;
        case 7:
        {}
            break;
        case 8:
        {}
            break;
        default:
            break;
    }
    event.Skip();
}


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Synth and Reverb", wxDefaultPosition, wxDefaultSize);
    frame->StartAudio();
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
