#pragma once

/////////////
// LINKING //
/////////////
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace GP
{

    class CDirect3D
    {
        CDirect3D();

        bool Init(int32_t windowWidth, int32_t windowHeight, bool vsync, HWND hWnd, bool fullscreen, float nearPlane, float farPlane);
        void Shutdown();

        void BeginScene(float red, float green, float blue, float alpha);
        void EndScene();

        ID3D11Device *GetDevice();
        ID3D11DeviceContext *GetDeviceContext();

        void GetWorldMatrix(XMMATRIX &worldMatrix) const;
        void GetOrthoMatrix(XMMATRIX &orthoMatrix) const;
        void GetProjectionMatrix(XMMATRIX &projectionMatrix) const;

        void GetVideoCardInfo(char *cardName, int32_t &memory) const;
        void SetBackBufferRenderTarget();
        void ResetViewport();

        void TurnZBufferOn();
        void TurnZBufferOff();

    private:
        IDXGISwapChain *m_SwapChain;
        ID3D11Device *m_Device;
        ID3D11DeviceContext *m_DeviceContext;
        ID3D11RenderTargetView *m_RenderTargetView;
        ID3D11Texture2D *m_DepthStencilBuffer;
        ID3D11DepthStencilView *m_DepthStencilState;
        ID3D11DepthStencilView *m_DepthStencilView;
        ID3D11RasterizerState *m_RasterizerState;
        ID3D11DepthStencilState *m_DepthDisabledStencilState;
        D3D11_VIEWPORT m_Viewport;
        XMMATRIX m_WorldMatrix;
        XMMATRIX m_OrthoMatrix;
        XMMATRIX m_ProjectionMatrix;
        char m_videoCardDescription[128];
        int32_t m_videoCardMemory;
        bool m_vsync;

        unsigned char _padding[11] = {};
    };

} // namespace GP
