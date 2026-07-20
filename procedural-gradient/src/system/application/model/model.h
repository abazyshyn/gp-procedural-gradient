#pragma once

namespace GP
{

    class CModel
    {
    public:
        CModel();

        bool Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext, std::string modelFilename);
        void Shutdown();
        void Render(ID3D11DeviceContext *deviceContext);

        int32_t GetIndexCount() const { return m_indexCount; };

    private:
        bool InitBuffers(ID3D11Device *device);
        void ShutdownBuffers();
        void RenderBuffers(ID3D11DeviceContext *deviceContext);
        bool LoadModel(std::string filename);

    private:
        struct Vertex_s
        {
            XMFLOAT3 position;
            float _padding;
        };

        struct Model_s
        {
            float x, y, z;
            float tu, tv;
            float nx, ny, nz;
        };

        std::vector<Model_s> m_modelData;
        ID3D11Buffer *m_vertexBuffer;
        ID3D11Buffer *m_indexBuffer;
        int32_t m_vertexCount;
        int32_t m_indexCount;
        int32_t m_rgbPosition;

        unsigned char _padding[4] = {};
    };

} // namespace GP
