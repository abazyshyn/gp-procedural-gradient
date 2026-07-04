#include "pch.h"

#include "model.h"

namespace GP
{

    bool CModel::Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext)
    {
        bool result = InitBuffers(device);
        if (!result)
        {
            return false;
        }

        return true;
    }

    void CModel::Shutdown()
    {
        ShutdownBuffers();
    }

    bool CModel::InitBuffers(ID3D11Device *device)
    {
        std::vector<Vertex_s> vertices{};
        m_vertexCount = static_cast<int32_t>(vertices.size());
        vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
        vertices[0].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
        vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
        vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
        vertices[2].position = XMFLOAT3(1.0f, -1.0f, 0.0f);
        vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
        vertices[3].position = XMFLOAT3(1.0f, 1.0f, 0.0f);
        vertices[3].color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

        std::vector<uint64_t> indices = {0, 1, 2, 2, 1, 3};
        m_indexCount = static_cast<int32_t>(indices.size());

        D3D11_BUFFER_DESC vertexBufferDescription{};
        vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDescription.ByteWidth = static_cast<uint32_t>(vertices.size()) * sizeof(Vertex_s);
        vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDescription.CPUAccessFlags = 0;
        vertexBufferDescription.MiscFlags = 0;
        vertexBufferDescription.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA vertexData{};
        vertexData.pSysMem = vertices.data();
        vertexData.SysMemPitch = 0;
        vertexData.SysMemSlicePitch = 0;

        if (FAILED(device->CreateBuffer(&vertexBufferDescription, &vertexData, &m_vertexBuffer)))
        {
            return false;
        }

        D3D11_BUFFER_DESC indexBufferDescription{};
        indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDescription.ByteWidth = static_cast<uint32_t>(indices.size()) * sizeof(uint64_t);
        indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDescription.CPUAccessFlags = 0;
        indexBufferDescription.MiscFlags = 0;
        indexBufferDescription.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA indexData{};
        indexData.pSysMem = indices.data();
        indexData.SysMemPitch = 0;
        indexData.SysMemSlicePitch = 0;

        if (FAILED(device->CreateBuffer(&indexBufferDescription, &indexData, &m_indexBuffer)))
        {
            return false;
        }

        return true;
    }

} // namespace GP
