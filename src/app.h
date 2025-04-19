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

// Need a forward declaration here
class GLCanvas;

// -------------------------------------------------------------------------------------
// GLFrame
class GLFrame : public wxFrame {
  public: 
    GLFrame();
    ~GLFrame();

  public:
    void OnPanelButton(wxCommandEvent& event);

  private: 
    GLCanvas* m_canvas = nullptr;

    wxBoxSizer* m_mainSizer   = nullptr;
    wxBoxSizer* m_bottomSizer = nullptr; 

    bool m_isPanelOpen = false;
};
// GLFrame
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// GLCanvas
class GLCanvas : public wxGLCanvas {
  public:
    GLCanvas(GLFrame* parent);
    ~GLCanvas();

  public:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnRotationSlider(wxCommandEvent& event);

  public: 
    wxBoxSizer* panelSizer = nullptr;

  private:
    void DrawCube();

    bool InitGL();

  private:
    wxGLContext* m_context = nullptr; 
    bool m_isGLInit        = false;
    wxSize m_cubeRotation  = wxSize(1, 1); 
};
// GLCanvas
// -------------------------------------------------------------------------------------
