#include "pch.h"

#include "application.h"

namespace GP
{

    bool CApplication::Init(int32_t windowWidth, int32_t windowHeight, HWND hWnd)
    {
        if (!m_Direct3D.Init(windowWidth, windowHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, NEAR_PLANE, FAR_PLANE))
        {
            MessageBox(hWnd, L"Could not initialize Direct3D", L"Error", MB_OK);
            return false;
        }

        if (!m_Model.Init(m_Direct3D.GetDevice(), m_Direct3D.GetDeviceContext()))
        {
            MessageBox(hWnd, L"Could not initialize model", L"Error", MB_OK);
            return false;
        }

        if (!m_PGradientShader.Init(m_Direct3D.GetDevice(), hWnd))
        {
            MessageBox(hWnd, L"Could not initialize pgradient shader", L"Error", MB_OK);
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

        // XMMATRIX worldMatrix{};
        // XMMATRIX viewMatrix{};
        // XMMATRIX projectionMatrix{};
        // m_Direct3D.GetWorldMatrix(worldMatrix);
        //// TODO: m_Camera.GetViewMatrix(viewMatrix);
        // m_Direct3D.GetProjectionMatrix(projectionMatrix);

        // m_Model.Render(m_Direct3D.GetDeviceContext());
        // m_PGradientShader.SetShaderMatrixBuffer(m_Direct3D.GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix);
        // m_PGradientShader.Render(m_Direct3D.GetDeviceContext(), m_Model.GetIndexCount());

        m_Direct3D.EndScene();

        return true;
    }

} // namespace GP
