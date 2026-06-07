#include "pch.h"

#include "direct3d.h"

namespace GP
{

    CDirect3D::CDirect3D()
        : m_SwapChain(nullptr),
          m_Device(nullptr),
          m_DeviceContext(nullptr),
          m_RenderTargetView(nullptr),
          m_DepthStencilBuffer(nullptr),
          m_DepthStencilState(nullptr),
          m_DepthStencilView(nullptr),
          m_RasterizerState(nullptr),
          m_DepthDisabledStencilState(nullptr)
    {
    }

    bool CDirect3D::Init(int32_t windowWidth, int32_t windowHeight, bool vsync, HWND hWnd, bool fullscreen, float nearPlane, float farPlane)
    {
        m_vsync = vsync;

        IDXGIFactory *factory = nullptr;
        if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&factory))))
        {
            return false;
        }

        return true;
    }

} // namespace GP
