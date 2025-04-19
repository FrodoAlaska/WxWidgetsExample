#include "app.h"

#include <wx/wx.h>

#define ID_PANEL_BUTTON (wxID_HIGHEST + 1)

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
  
  // Setting OpenGL attributes
  wxGLAttributes attribs;
  attribs.RGBA().DoubleBuffer().EndList();
  
  // Setting the sizer
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(m_canvas);

  // Creating components
  wxBoxSizer* otherSizer = new wxBoxSizer(wxHORIZONTAL);
  wxButton* panelButton = new wxButton(this, ID_PANEL_BUTTON, "Open Panel");
  otherSizer->Add(panelButton);
  
  sizer->Add(otherSizer);
  SetSizerAndFit(sizer);

  Bind(wxEVT_BUTTON, &GLFrame::OnPanelButton, this);
}

GLFrame::~GLFrame() 
{

}

void GLFrame::OnPanelButton(wxCommandEvent& event) 
{
  m_isPanelOpen = !m_isPanelOpen;
  wxLogMessage("Not here, idiot!");
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
  contextAttrs.CompatibilityProfile().OGLVersion(2, 2).Robust().EndList();
  
  // Create the OpenGL context
  m_context = new wxGLContext(this);
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
 
  DrawCube(1, 1);  

  glFlush();
  SwapBuffers();
}

void GLCanvas::OnSize(wxSizeEvent& event) 
{
  auto size = event.GetSize() * GetContentScaleFactor();
  glViewport(0, 0, size.x, size.y);

  Refresh();
}
    
void GLCanvas::DrawCube(int xAngle, int yAngle) 
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -2.0f);
   glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
   glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

   glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
   
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
   glEnd();

   glFlush();
}

bool GLCanvas::InitGL() 
{
  // Set the OpenGL context
  SetCurrent(*m_context);

  // Set some OpenGL states
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  return true;
}
 
// GLCanvas functions
// -------------------------------------------------------------------------------------
