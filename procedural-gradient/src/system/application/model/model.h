#pragma once

namespace GP
{

    class CModel
    {
    public:
        bool Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext);
        void Shutdown();
        void Render(ID3D11DeviceContext *deviceContext);

        inline int32_t GetIndexCount() const;

    private:
        bool InitBuffers(ID3D11Device *device);
        void ShutdownBuffers();
        void RenderBuffers();

    private:
        struct Vertex_s
        {
            XMFLOAT3 position;
            XMFLOAT4 color;
        };

        ID3D11Buffer *m_vertexBuffer;
        ID3D11Buffer *m_indexBuffer;
        int32_t m_vertexCount;
        int32_t m_indexCount;
    };

} // namespace GP
