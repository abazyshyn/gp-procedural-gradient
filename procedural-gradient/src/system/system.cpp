#include "pch.h"

#include "system.h"

namespace GP
{

    bool CSystem::Init()
    {
        int32_t windowWidth = 0;
        int32_t windowHeight = 0;
        InitWindows(windowWidth, windowHeight);

        return true;
    }

    void CSystem::Run()
    {
        MSG msg{};

        for (;;)
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            if (msg.message == WM_QUIT)
            {
                break;
            }

            if (!Frame())
            {
                break;
            }
        }
    }

    void CSystem::Shutdown()
    {
        ShutdownWindows();
    }

    LRESULT CSystem::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            default:
            {
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }

        return 0;
    }

    bool CSystem::Frame()
    {
        return true;
    }

    void CSystem::InitWindows(int32_t &windowWidth, int32_t &windowHeight)
    {
        applicationHandler = this;

        m_hInstance = GetModuleHandle(nullptr);
        m_applicationName = L"Procedural Gradient";

        WNDCLASSEX wc{};
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_hInstance;
        wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
        wc.hIconSm = wc.hIcon;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = m_applicationName;
        wc.cbSize = sizeof(WNDCLASSEX);

        RegisterClassEx(&wc);

        windowWidth = GetSystemMetrics(SM_CXSCREEN);
        windowHeight = GetSystemMetrics(SM_CYSCREEN);

        int32_t posX{};
        int32_t posY{};
        if (false) // TODO: Fullscreen global
        {
            DEVMODE dmScreenSettings{};
            dmScreenSettings.dmSize = sizeof(dmScreenSettings);
            dmScreenSettings.dmPelsWidth = static_cast<unsigned long>(windowWidth);
            dmScreenSettings.dmPelsHeight = static_cast<unsigned long>(windowHeight);
            dmScreenSettings.dmBitsPerPel = 32;
            dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

            ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

            posX = 0;
            posY = 0;
        }
        else
        {
            windowWidth = 800;
            windowHeight = 600;

            posX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) >> 1;
            posY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) >> 1;
        }

        m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
                                posX, posY, windowWidth, windowHeight, nullptr, nullptr, m_hInstance, nullptr);
        ShowWindow(m_hWnd, SW_SHOW);
        SetForegroundWindow(m_hWnd);
        SetFocus(m_hWnd);
        ShowCursor(true); // TODO: control
    }

    void CSystem::ShutdownWindows()
    {
        ShowCursor(true);

        if (false) // TODO: Fullscreen global
        {
            ChangeDisplaySettings(nullptr, 0);
        }

        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;

        UnregisterClass(m_applicationName, m_hInstance);
        m_hInstance = nullptr;
    }

    LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }
            case WM_CLOSE:
            {
                PostQuitMessage(0);
                return 0;
            }
            default:
            {
                return applicationHandler->MessageHandler(hWnd, uMsg, wParam, lParam);
            }
        }
    }

} // namespace GP
