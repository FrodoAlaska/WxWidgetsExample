#include "app.h"
#include "app_frame.h"

#include <wx/wx.h>

// -------------------------------------------------------------------------------------
// ExampleApp functions

bool ExampleApp::OnInit() 
{
  wxInitAllImageHandlers();
  AppFrame* frame = new AppFrame();
  frame->Show(true);

  return true;
}

// ExampleApp functions
// -------------------------------------------------------------------------------------
