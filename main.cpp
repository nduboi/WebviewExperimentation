#include <iostream>
#include "webview/webview.h"

void changeSettings(webview::result<void*> &optional) {
    ICoreWebView2Settings *m_settings = nullptr;
    ICoreWebView2Settings6 *m_settings6 = nullptr;

    if (optional.has_value()) {
        auto m_webviewController = static_cast<ICoreWebView2Controller *>(optional.value());
        ICoreWebView2 *m_webview = nullptr;
        m_webviewController->get_CoreWebView2(&m_webview);
        if (!m_webview) {
            MessageBoxA(nullptr, "Failed to get ICoreWebView2 with ICoreWebView2Controller!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        auto res = m_webview->get_Settings(&m_settings);
        if (!m_settings || res != S_OK) {
            MessageBoxA(nullptr, "Failed to get webview settings!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        res = m_settings->QueryInterface(IID_ICoreWebView2Settings6, reinterpret_cast<void **>(&m_settings6));
        if (res != S_OK || !m_settings6) {
            MessageBoxA(nullptr, "Failed to get webview settings6!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        res = m_settings6->put_IsPinchZoomEnabled(false);
        if (res != S_OK) {
            MessageBoxA(nullptr, "Failed to disabled Pinch Zoom!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        res = m_settings6->put_IsSwipeNavigationEnabled(false);
        if (res != S_OK) {
            MessageBoxA(nullptr, "Failed to disabled Swipe Navigation!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        m_settings6->Release();
        res = m_settings6->put_IsZoomControlEnabled(false);
        if (res != S_OK) {
            MessageBoxA(nullptr, "Failed to disabled Zoom Control!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        res = m_settings6->put_IsGeneralAutofillEnabled(false);
        if (res != S_OK) {
            MessageBoxA(nullptr, "Failed to disabled General Auto fill!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
        res = m_settings6->put_AreDefaultContextMenusEnabled(false);
        if (res != S_OK) {
            MessageBoxA(nullptr, "Failed to disabled General Auto fill!\nPlease update Webview2.", "Webview Settings", MB_ICONERROR);
            exit(1);
        }
    }
}

int main(int ac, char *argv[])
{
    try {
        webview::webview w(false, nullptr);
        webview::result<void*> optional = w.browser_controller();
        changeSettings(optional);
        w.set_title("Basic Example");
        w.set_size(480, 320, WEBVIEW_HINT_NONE);
        w.set_html("<p>Hello, World!</p> <button onclick=\"__cpp_reloadHtml()\">Refresh Page</button>");
        w.bind("__cpp_reloadHtml", [&w](const std::string &t) -> std::string {
            w.set_html("<button onclick=\"__cpp_reloadHtml()\">Refresh Page</button><p>Page refreshed</p>");
            return "";
        });
        w.run();
        w.terminate();
    } catch (const webview::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}