#pragma once

#include <wx/wx.h>
#include <wx/clrpicker.h>

// Need a forward declaration here
class AppCanvas;

// -------------------------------------------------------------------------------------
// AppFrame
class AppFrame : public wxFrame {
  public: 
    AppFrame();
    ~AppFrame();

  public:
    void OnPanelButton(wxCommandEvent& event);
    void OnSlider(wxCommandEvent& event);
    void OnCheckBox(wxCommandEvent& event);
    void OnColorPicker(wxColourPickerEvent& event);

  private: 
    AppCanvas* m_canvas = nullptr;

    wxBoxSizer* m_mainSizer   = nullptr;
    wxBoxSizer* m_bottomSizer = nullptr; 
    wxBoxSizer* m_panelSizer  = nullptr;

    bool m_isPanelOpen     = false;
};
// AppFrame
// -------------------------------------------------------------------------------------
