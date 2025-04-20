#include "app_frame.h"
#include "app_canvas.h"

#include <wx/wx.h>

// -------------------------------------------------------------------------------------
// WidgetsID
enum WidgetsID 
{
  ID_PANEL_BUTTON = wxID_HIGHEST + 1,

  ID_PANEL_SLIDER,
  ID_PANEL_CHECKBOX,
  ID_PANEL_COLOR_PICKER,
};
// WidgetsID
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// AppFrame functions

AppFrame::AppFrame()
  : wxFrame(nullptr, wxID_ANY, "OpenGL Example") 
{
  // Sizers init
  m_mainSizer   = new wxBoxSizer(wxVERTICAL);
  m_bottomSizer = new wxBoxSizer(wxHORIZONTAL); 
  m_panelSizer  = new wxBoxSizer(wxHORIZONTAL); 
  
  // OpenGL canvas init
  m_canvas = new AppCanvas(this); 
  m_canvas->SetMinSize(FromDIP(wxSize(640, 480)));
  
  // Setting OpenGL attributes
  wxGLAttributes attribs;
  attribs.RGBA().DoubleBuffer().EndList();
  
  // Main sizer components init
  m_mainSizer->Add(m_canvas);
  m_mainSizer->Add(m_bottomSizer);
  m_mainSizer->Add(m_panelSizer);

  // Bottom sizer components init
  m_bottomSizer->Add(new wxButton(this, ID_PANEL_BUTTON, "Open Panel"));
  
  // Panel sizer components init
  m_panelSizer->Add(new wxSlider(this, ID_PANEL_SLIDER, 1, 1, 100)); 
  m_panelSizer->Add(new wxCheckBox(this, ID_PANEL_CHECKBOX, "Wireframe Mode"));
  m_panelSizer->Add(new wxColourPickerCtrl(this, ID_PANEL_COLOR_PICKER));

  // Re-fit
  SetSizerAndFit(m_mainSizer);
  m_panelSizer->ShowItems(false);
  
  // Binding events
  Bind(wxEVT_BUTTON, &AppFrame::OnPanelButton, this);
  Bind(wxEVT_SCROLL_CHANGED, &AppFrame::OnSlider, this);
  Bind(wxEVT_CHECKBOX, &AppFrame::OnCheckBox, this);
  Bind(wxEVT_COLOURPICKER_CHANGED, &AppFrame::OnColorPicker, this);
}

AppFrame::~AppFrame() 
{
  delete m_canvas;
}

void AppFrame::OnPanelButton(wxCommandEvent& event) 
{
  // Open or close the panel 
  m_isPanelOpen = !m_isPanelOpen;
  m_panelSizer->ShowItems(m_isPanelOpen);
}

void AppFrame::OnSlider(wxCommandEvent& event) 
{
  int value = event.GetInt(); 
  
  m_canvas->quadRect.width  = value;
  m_canvas->quadRect.height = value;
  
  m_canvas->Refresh();
}
  
void AppFrame::OnCheckBox(wxCommandEvent& event) 
{
  // Change the canvas's draw mode based on the checkbox's "check" status.
  if(event.IsChecked()) 
    m_canvas->polygonMode = GL_LINE;
  else 
    m_canvas->polygonMode = GL_FILL;
  
  m_canvas->Refresh();
  SetSizerAndFit(m_mainSizer);
}
 
void AppFrame::OnColorPicker(wxColourPickerEvent& event) 
{
  wxColour colorValue = event.GetColour();

  // OpenGL handles colors as floats. So any value between 0.0f and 1.0f 
  // is a valid color. However, wxWidgets handles colors as an `int`. 
  // Any value between 0 and 255 is valid color. This is just here to 
  // convert between the two ranges.
  m_canvas->quadColor.r = colorValue.Red() / 255.0f;
  m_canvas->quadColor.g = colorValue.Green() / 255.0f;
  m_canvas->quadColor.b = colorValue.Blue() / 255.0f;

  m_canvas->Refresh();
}

// AppFrame functions
// -------------------------------------------------------------------------------------
