#pragma once 

#include "app_frame.h"

#include <wx/wx.h>
#include <wx/glcanvas.h>

// -------------------------------------------------------------------------------------
// Color
struct Color 
{
  float r, g, b, a;

  Color()
    :r(0.0f), g(0.0f), b(0.0f), a(0.0f)
  {}
  
  Color(float r, float g, float b, float a = 1.0f)
    :r(r), g(g), b(b), a(a)
  {}
  
  Color(float rgba)
    :r(rgba), g(rgba), b(rgba), a(rgba)
  {}
};
// Color
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// DrawRectangle 
struct DrawRectangle 
{
  float x, y; 
  float width, height;
  
  DrawRectangle() 
    :x(0.0f), y(0.0f), width(0.0f), height(0.0f)
  {}

  DrawRectangle(float x, float y, float width, float height) 
    :x(x), y(y), width(width), height(height)
  {}
  
  DrawRectangle(float xy, float size) 
    :x(xy), y(xy), width(size), height(size)
  {}
};
// DrawRectangle 
// -------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------
// AppCanvas
class AppCanvas : public wxGLCanvas {
  public:
    AppCanvas(AppFrame* parent);
    ~AppCanvas();

  public:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
  
    int CreateTexture(const char* path);

    void DrawQuad(const DrawRectangle& rect, const Color& col);
    void DrawQuad(const DrawRectangle& rect, const int textureID);
   
  public:
    bool isWireframeMode = false;
    int polygonMode;
    
    DrawRectangle quadRect;
    Color quadColor;

  private:
    bool InitGL();

  private:
    wxGLContext* m_context = nullptr; 
    bool m_isGLInit        = false;
};
// AppCanvas
// -------------------------------------------------------------------------------------
