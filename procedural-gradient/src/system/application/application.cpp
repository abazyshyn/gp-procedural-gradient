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

        result = m_Model.Init(m_Direct3D.GetDevice(), m_Direct3D.GetDeviceContext());
        if (!result)
        {
            MessageBox(hWnd, L"Could not initialize model", L"Error", MB_OK);
            return false;
        }

        return true;
    }

    void CApplication::Shutdown()
    {
        m_Direct3D.Shutdown();
        m_Model.Shutdown();
    }

    bool CApplication::Frame()
    {
        if (!Render())
        {
            return false;
        }

        return true;
    }

    bool CApplication::Render()
    {
        m_Direct3D.BeginScene(1.0f, 1.0f, 1.0f, 1.0f);

        XMMATRIX worldMatrix{};
        XMMATRIX viewMatrix{};
        XMMATRIX projectionMatrix{};
        m_Direct3D.GetWorldMatrix(worldMatrix);
        // TODO: m_Camera.GetViewMatrix(viewMatrix);
        m_Direct3D.GetProjectionMatrix(projectionMatrix);

        m_Model.Render(m_Direct3D.GetDeviceContext());

        // TODO: Procedural gradient shader

        m_Direct3D.EndScene();

        return true;
    }

} // namespace GP
