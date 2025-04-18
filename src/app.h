#pragma once 

#include <wx/wxprec.h>
#define WX_PRECOMP
#include <wx/wx.h>

#include <glad/glad.h>
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
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

  private: 
    GLCanvas* m_canvas = nullptr;
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

  private:
    void CheckCompileErrors(int shader);
    void CheckLinkerErrors(int program);

    bool InitGL();
    void InitBuffers();
    void InitShaders();

  private:
    wxGLContext* m_context = nullptr; 
    bool m_isGLInit        = false;

    unsigned int m_vao, m_ebo, m_vbo, m_shader;
};
// GLCanvas
// -------------------------------------------------------------------------------------
