#include "pch.h"

#include "application.h"

namespace GP
{

    bool CApplication::Init(int32_t windowWidth, int32_t windowHeight, HWND hWnd)
    {
        bool result{};

        result = m_Direct3D.Init(windowWidth, windowHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, NEAR_PLANE, FAR_PLANE);
        if (!result)
        {
            MessageBox(hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
            return false;
        }

        return true;
    }

} // namespace GP
