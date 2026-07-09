#pragma once

namespace GP
{

    class CModel
    {
    public:
        CModel();

        bool Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext);
        void Shutdown();
        void Render(ID3D11DeviceContext *deviceContext);

        int32_t GetIndexCount() const { return m_indexCount; };

    private:
        bool InitBuffers(ID3D11Device *device);
        void ShutdownBuffers();
        void RenderBuffers(ID3D11DeviceContext *deviceContext);

    private:
        struct Vertex_s
        {
            XMFLOAT3 position;
        };

        ID3D11Buffer *m_vertexBuffer;
        ID3D11Buffer *m_indexBuffer;
        int32_t m_vertexCount;
        int32_t m_indexCount;
        int32_t m_rgbPosition;
    };

} // namespace GP
