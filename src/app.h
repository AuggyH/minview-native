#pragma once
#include "window.h"
#include "renderer.h"
#include "decoder.h"
#include <string>
#include <vector>
#include <memory>

namespace mv {

/// Main application — orchestrates window, rendering, and image loading.
class App {
public:
    App();
    ~App();

    /// Run the application. Returns exit code.
    int run(const std::wstring& initial_path = L"");

private:
    LRESULT handle_message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    void    open_image(const std::wstring& path);
    void    render_frame();

    Window   m_window;
    Renderer m_renderer;
    Decoder  m_decoder;

    std::wstring m_current_path;
    bool         m_has_image = false;
};

} // namespace mv
