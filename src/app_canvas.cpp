#include "app_canvas.h"

#include <wx/wx.h>

// -------------------------------------------------------------------------------------
// AppCanvas functions

AppCanvas::AppCanvas(AppFrame* parent) 
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
  Bind(wxEVT_PAINT, &AppCanvas::OnPaint, this);
  Bind(wxEVT_SIZE, &AppCanvas::OnSize, this);
  
  // OpenGL init
  InitGL();
  
  // Setting default values
  polygonMode = GL_FILL;
  quadRect    = DrawRectangle(10.0f, 32.0f);
  quadColor   = Color(1.0f);
}

AppCanvas::~AppCanvas() 
{
  delete m_context;
}

void AppCanvas::OnPaint(wxPaintEvent& event) 
{
  SetCurrent(*m_context);
  wxPaintDC(this);
 
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  wxSize size = GetSize();
  glViewport(0, 0, size.x, size.y);
  
  glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
  DrawQuad(quadRect, quadColor); 

  glFlush();
  SwapBuffers();
}

void AppCanvas::OnSize(wxSizeEvent& event) 
{
  wxSize size = event.GetSize();
  glViewport(0, 0, size.x, size.y);

  Refresh();
}

int AppCanvas::CreateTexture(const char* path) 
{
  unsigned int id = -1; 

  // Texture init
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  // Loading the texture data at `path`. 
  wxImage img;
  if(!img.LoadFile(wxString(path))) 
  {
    wxLogError("Failed to load texture at \'%s\'", path);
    return -1;
  }

  // Setting the texture's data;
  glTexImage2D(GL_TEXTURE_2D, 
               0, 
               GL_RGBA, 
               img.GetWidth(), img.GetHeight(),
               0, 
               GL_RGBA, 
               GL_UNSIGNED_BYTE, 
               img.GetData());

  // Setting texture parameters
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);
  return id;
}

void AppCanvas::DrawQuad(const DrawRectangle& rect, const Color& col) 
{
  glPushMatrix();
  glTranslatef(rect.x, rect.y, 0.0f);
  glScalef(rect.width, rect.height, 1.0f);

  glBegin(GL_QUADS);
    glColor3f(col.r, col.g, col.b);

    glVertex2f(-0.5f,  0.5f); 
    glVertex2f( 0.5f,  0.5f); 
    glVertex2f( 0.5f, -0.5f); 
    glVertex2f(-0.5f, -0.5f); 
  glEnd();
  glPopMatrix();
}

void AppCanvas::DrawQuad(const DrawRectangle& rect, const int textureID) 
{
  if(textureID == -1) 
  {
    wxLogError("Cannot draw a textured quad with an invalid texture ID");
    return;
  }

  glBindTexture(GL_TEXTURE_2D, textureID);
  glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(rect.x, rect.y); 
    glTexCoord2f(0, 1); 

    glVertex2f(rect.x + rect.width, rect.y); 
    glTexCoord2f(1, 1); 

    glVertex2f(rect.x + rect.width, rect.y + rect.height); 
    glTexCoord2f(1, 0); 

    glVertex2f(rect.x, rect.y + rect.height); 
    glTexCoord2f(0, 0); 
  glEnd();
}

bool AppCanvas::InitGL() 
{
  // Set the OpenGL context
  SetCurrent(*m_context);

  // Set some OpenGL states
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_TEXTURE_2D);
  
  // Set viewing projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Setting the orthographics matrix
  wxSize size = GetSize();
  glOrtho(0, size.x, size.y, 0, -1, 100);

  return true;
}
 
// AppCanvas functions
// -------------------------------------------------------------------------------------
