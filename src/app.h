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
    void OnSlider(wxCommandEvent& event);
    void OnCheckBox(wxCommandEvent& event);

  private: 
    GLCanvas* m_canvas = nullptr;

    wxBoxSizer* m_mainSizer   = nullptr;
    wxBoxSizer* m_bottomSizer = nullptr; 
    wxBoxSizer* m_panelSizer  = nullptr;

    bool m_isPanelOpen     = false;
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
    void Render();
   
  public:
    float cubeRotation   = 1.0f;
    bool isWireframeMode = false;
    int polygonMode;

  private:
    void DrawCube();

    bool InitGL();

  private:
    wxGLContext* m_context = nullptr; 
    bool m_isGLInit        = false;
};
// GLCanvas
// -------------------------------------------------------------------------------------
