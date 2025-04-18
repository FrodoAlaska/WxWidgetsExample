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
  contextAttrs.CoreProfile().OGLVersion(4, 5).Robust().EndList();
  
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

  InitGL();
}

GLCanvas::~GLCanvas() 
{
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
  glDeleteProgram(m_shader);

  delete m_context;
}

void GLCanvas::OnPaint(wxPaintEvent& event) 
{
  wxPaintDC dc(this);
  SetCurrent(*m_context);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(m_shader);
  
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  SwapBuffers();
}

void GLCanvas::OnSize(wxSizeEvent& event) 
{
  auto viewPortSize = event.GetSize() * GetContentScaleFactor();
  glViewport(0, 0, viewPortSize.x, viewPortSize.y);

  Refresh();
  event.Skip();
}

void GLCanvas::CheckCompileErrors(int shader) {
  int success;
  char logInfo[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success); 

  if(!success) {
    glGetShaderInfoLog(shader, 512, nullptr, logInfo);
    wxLogDebug("SHADER-ERROR: %s", logInfo);
  }
}

void GLCanvas::CheckLinkerErrors(int program) {
  int success;
  char logInfo[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success); 

  if(!success) {
    glGetProgramInfoLog(program, 512, nullptr, logInfo);
    wxLogDebug("SHADER-ERROR: %s", logInfo);
  }
}

bool GLCanvas::InitGL() 
{
  // Init GLAD
  SetCurrent(*m_context);
  if(!gladLoadGL()) {
    wxMessageBox("Could not load GLAD", "OPENGL ERROR", wxOK | wxICON_ERROR);
    return false;
  }
  wxLogDebug("HERE");

  // Set the current context
  SetCurrent(*m_context);
  m_isGLInit = true;

  // Set some OpenGL states
  glEnable(GL_DEPTH_TEST);

  // Init the default buffers
  InitBuffers();

  // Init the default shaders
  InitShaders();

  return true;
}

void GLCanvas::InitBuffers() 
{
  // Vertices
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f, 
     0.5f,  0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f, 
  };

  // Indices
  int indices[] = {
    0, 1, 2, 
    2, 3, 0,
  };

  // Init VAO
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  // Init EBO
  glGenBuffers(1, &m_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  
  // Buffer data
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Init VBO
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
 
  // Buffer data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void GLCanvas::InitShaders() 
{
  const char* vertexSrc =
    "#version 460 core"
    "\n"
    "layout (location = 0) in vec3 aPos;"
    "\n"   
    "void main()"
    "{"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
    "}";

  const char* fragmentSrc = 
    "#version 460 core"
    "\n"
    "layout (location = 0) out vec4 fragColor;"
    "uniform vec4 u_color;"
    "\n"
    "void main()"
    "{"
    "   fragColor = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";

  // Vertex shader init
  int vertexID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexID, 1, &vertexSrc, nullptr); 
  glCompileShader(vertexID);
  CheckCompileErrors(vertexID);
  
  // Fragment shader init
  int fragID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragID, 1, &fragmentSrc, nullptr); 
  glCompileShader(fragID);
  CheckCompileErrors(fragID);
  
  // Shader program init
  m_shader = glCreateProgram();
  glAttachShader(m_shader, vertexID);
  glAttachShader(m_shader, fragID);
  glLinkProgram(m_shader);
  CheckLinkerErrors(m_shader);
  
  // Detaching
  glDetachShader(m_shader, vertexID);
  glDetachShader(m_shader, fragID);
  glDeleteShader(vertexID);
  glDeleteShader(fragID);
}
 
// GLCanvas functions
// -------------------------------------------------------------------------------------
