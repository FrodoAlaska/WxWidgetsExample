#include "app.h"

#include <wx/wx.h>

// -------------------------------------------------------------------------------------
// WidgetsID
enum WidgetsID 
{
  ID_PANEL_BUTTON = wxID_HIGHEST + 1,

  ID_PANEL_SLIDER,
  ID_PANEL_CHECKBOX,
};
// WidgetsID
// -------------------------------------------------------------------------------------

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
  // Sizers init
  m_mainSizer   = new wxBoxSizer(wxVERTICAL);
  m_bottomSizer = new wxBoxSizer(wxHORIZONTAL); 
  m_panelSizer  = new wxBoxSizer(wxVERTICAL); 
  
  // OpenGL canvas init
  m_canvas = new GLCanvas(this); 
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

  // Re-fit
  SetSizerAndFit(m_mainSizer);
  m_panelSizer->ShowItems(false);
  
  // Binding events
  Bind(wxEVT_BUTTON, &GLFrame::OnPanelButton, this);
  Bind(wxEVT_SCROLL_CHANGED, &GLFrame::OnSlider, this);
  Bind(wxEVT_CHECKBOX, &GLFrame::OnCheckBox, this);
}

GLFrame::~GLFrame() 
{
  delete m_canvas;
}

void GLFrame::OnPanelButton(wxCommandEvent& event) 
{
  m_isPanelOpen = !m_isPanelOpen;
  m_panelSizer->ShowItems(m_isPanelOpen);
}

void GLFrame::OnSlider(wxCommandEvent& event) 
{
  int value = event.GetInt(); 

  m_canvas->cubeRotation = value;
  m_canvas->Refresh();
}
  
void GLFrame::OnCheckBox(wxCommandEvent& event) 
{
  if(event.IsChecked()) 
    m_canvas->polygonMode = GL_LINE;
  else 
    m_canvas->polygonMode = GL_FILL;
  
  m_canvas->Refresh();
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
  
  // Setting default values
  polygonMode = GL_FILL;
}

GLCanvas::~GLCanvas() 
{
  delete m_context;
}

void GLCanvas::OnPaint(wxPaintEvent& event) 
{
  Render();
}

void GLCanvas::OnSize(wxSizeEvent& event) 
{
  wxSize size = event.GetSize() * GetContentScaleFactor();
  glViewport(0, 0, size.x, size.y);

  Refresh();
}
   
void GLCanvas::Render() 
{
  SetCurrent(*m_context);
  wxPaintDC(this);
 
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  wxSize size = GetSize() * GetContentScaleFactor();
  glViewport(0, 0, size.x, size.y);
  
  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
  DrawCube();  

  SwapBuffers();
}

void GLCanvas::DrawCube() 
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Translation
   glTranslatef(0.0f, 0.0f, -1.0f);

   // Rotation
   glRotatef(cubeRotation, 1.0f, 1.0f, 1.0f);

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f,-0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    
    glVertex3f(-0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f,-0.5f);
    glVertex3f( 0.5f,-0.5f, 0.5f);
    glVertex3f(-0.5f,-0.5f, 0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
   
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
   glEnd();

   glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    
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
