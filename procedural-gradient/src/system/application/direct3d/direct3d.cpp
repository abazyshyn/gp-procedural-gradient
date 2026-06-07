#include "pch.h"

#include "direct3d.h"

namespace GP
{

    CDirect3D::CDirect3D()
        : m_swapChain(nullptr),
          m_device(nullptr),
          m_deviceContext(nullptr),
          m_renderTargetView(nullptr),
          m_depthStencilBuffer(nullptr),
          m_depthStencilState(nullptr),
          m_depthStencilView(nullptr),
          m_rasterizerState(nullptr),
          m_depthDisabledStencilState(nullptr)
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

        IDXGIAdapter *adapter = nullptr;
        if (FAILED(factory->EnumAdapters(0, &adapter)))
        {
            return false;
        }

        IDXGIOutput *adapterOutput = nullptr;
        if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
        {
            return false;
        }

        uint32_t countModes{};
        if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &countModes, nullptr)))
        {
            return false;
        }

        std::vector<DXGI_MODE_DESC> displayModes;
        if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &countModes, displayModes.data())))
        {
            return false;
        }

        uint32_t refreshRateNumenator{};
        uint32_t refreshRateDenominator{};
        for (const DXGI_MODE_DESC &displayMode : displayModes)
        {
            if (displayMode.Width == static_cast<uint32_t>(windowWidth) && displayMode.Height == static_cast<uint32_t>(windowHeight))
            {
                refreshRateNumenator = displayMode.RefreshRate.Numerator;
                refreshRateDenominator = displayMode.RefreshRate.Denominator;
                break;
            }
        }

        // Get the adapter (video card) description
        DXGI_ADAPTER_DESC adapterDescription{};
        if (FAILED(adapter->GetDesc(&adapterDescription)))
        {
            return false;
        }

        // Store the dedicated video card memory in megabytes
        constexpr size_t SZ_KILOBYTES = 1024;
        constexpr size_t SZ_MEGABYTES = 1024;
        m_videoCardMemory = static_cast<int32_t>(adapterDescription.DedicatedVideoMemory / SZ_KILOBYTES / SZ_MEGABYTES);

        size_t stringLength{};
        if (wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDescription.Description, 128))
        {
            return false;
        }

        // Release unused data
        adapterOutput->Release();
        adapterOutput = nullptr;

        adapter->Release();
        adapter = nullptr;

        factory->Release();
        factory = nullptr;

        DXGI_SWAP_CHAIN_DESC swapChainDescription{};
        swapChainDescription.BufferCount = 1;
        swapChainDescription.BufferDesc.Width = windowWidth;
        swapChainDescription.BufferDesc.Height = windowHeight;
        swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDescription.BufferDesc.RefreshRate.Numerator = m_vsync ? refreshRateNumenator : 0;
        swapChainDescription.BufferDesc.RefreshRate.Denominator = m_vsync ? refreshRateDenominator : 0;
        swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDescription.OutputWindow = hWnd;
        swapChainDescription.SampleDesc.Count = 1;   // Turn multisampling off
        swapChainDescription.SampleDesc.Quality = 0; //
        swapChainDescription.Windowed = !fullscreen;
        swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDescription.Flags = 0;

        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

        if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION,
                                                 &swapChainDescription, &m_swapChain, &m_device, nullptr, &m_deviceContext)))
        {
            return false;
        }

        ID3D11Texture2D *backBuffer = nullptr;
        if (FAILED(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&backBuffer))))
        {
            return false;
        }

        return true;
    }

} // namespace GP
