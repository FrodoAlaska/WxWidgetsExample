#pragma once 

#include <wx/wxprec.h>
#define WX_PRECOMP
#include <wx/wx.h>

#include <wx/glcanvas.h>

// -------------------------------------------------------------------------------------
// ExampleApp
class ExampleApp : public wxApp {
  public: 
    bool OnInit() override;
};

wxDECLARE_APP(ExampleApp);
// ExampleApp
// -------------------------------------------------------------------------------------
