#pragma once

namespace GP
{

    class CSystem
    {
    public:
        CSystem();

        bool Init();
        void Run();
        void Shutdown();

        LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private:
        bool Frame();
        void InitWindows(int32_t &windowWidth, int32_t &windowHeight);
        void Shutdown();

    private:
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        LPCWSTR m_applicationName;
    };

    /////////////////////////
    // FUNCTION PROTOTYPES //
    /////////////////////////
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

} // namespace GP
