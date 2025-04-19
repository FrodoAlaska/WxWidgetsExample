#include "app.h"

#include <wx/wx.h>

#define ID_HELLO 1

// -------------------------------------------------------------------------------------
// ExampleApp functions

bool ExampleApp::OnInit() 
{
  GLFrame* frame = new GLFrame();
  frame->Show(true);

  return true;
}

// ExampleApp functions
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// GLFrame functions

GLFrame::GLFrame()
  : wxFrame(nullptr, wxID_ANY, "OpenGL Example") 
{
  // OpenGL canvas init
  m_canvas = new GLCanvas(this); 
  m_canvas->SetMinSize(FromDIP(wxSize(640, 480)));
  
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(m_canvas, 1, wxEXPAND);
}

GLFrame::~GLFrame() 
{

}

void GLFrame::OnHello(wxCommandEvent& event) 
{
  wxLogMessage("Hey, there!");
}

void GLFrame::OnExit(wxCommandEvent& event) 
{
  Close(true);
}

void GLFrame::OnAbout(wxCommandEvent& event) 
{
  wxMessageBox("Important information", "About Me: ", wxOK | wxICON_INFORMATION);
}

// GLFrame functions
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// GLCanvas functions

GLCanvas::GLCanvas(GLFrame* parent) 
  : wxGLCanvas(parent) 
{
  // Set some useful attributes for OpenGL
  wxGLContextAttrs contextAttrs; 
  contextAttrs.CoreProfile().OGLVersion(3, 3).Robust().EndList();
  
  // Create the OpenGL context
  m_context = new wxGLContext(this, nullptr, &contextAttrs);
  if(!m_context->IsOK()) 
  {
    wxMessageBox("Could not load OpenGL version CORE 4.5", "OPENGL ERROR", wxOK | wxICON_ERROR);
    delete m_context;

    return;
  }
  
  // Bind our own functions for the pain and resize events
  Bind(wxEVT_PAINT, &GLCanvas::OnPaint, this);
  Bind(wxEVT_SIZE, &GLCanvas::OnSize, this);
  
  // OpenGL init
  InitGL();
    
  // Set viewing projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.5, 0.5, -0.5, 0.5, 0.1, 100.0);
}

GLCanvas::~GLCanvas() 
{
  delete m_context;
}

void GLCanvas::OnPaint(wxPaintEvent& event) 
{
  SetCurrent(*m_context);
  wxPaintDC(this);
 
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto size = GetSize();
  glViewport(0, 0, size.x, size.y);
 
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f,  0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f( 0.5f, -0.5f);
  glEnd();

  glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f( 0.1f,  0.1f);
    glVertex2f(-0.1f,  0.1f);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f( 0.1f, -0.1f);
  glEnd();
  
  glFlush();
  SwapBuffers();
}

void GLCanvas::OnSize(wxSizeEvent& event) 
{
  auto size = event.GetSize() * GetContentScaleFactor();
  glViewport(0, 0, size.x, size.y);

  Refresh();
}

bool GLCanvas::InitGL() 
{
  // Set the OpenGL context
  SetCurrent(*m_context);

  // Set some OpenGL states
  glEnable(GL_DEPTH_TEST);

  return true;
}
 
// GLCanvas functions
// -------------------------------------------------------------------------------------
