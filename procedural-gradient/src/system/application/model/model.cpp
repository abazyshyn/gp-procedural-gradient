#include "pch.h"

#include "model.h"

namespace GP
{

    CModel::CModel()
        : m_vertexBuffer(nullptr),
          m_indexBuffer(nullptr),
          m_vertexCount(0),
          m_indexCount(0)
    {
    }

    bool CModel::Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext)
    {
        if (!InitBuffers(device))
        {
            return false;
        }

        return true;
    }

    void CModel::Shutdown()
    {
        ShutdownBuffers();
    }

    void CModel::Render(ID3D11DeviceContext *deviceContext)
    {
        RenderBuffers(deviceContext);
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

    void CModel::ShutdownBuffers()
    {
        if (m_vertexBuffer)
        {
            m_vertexBuffer->Release();
            m_vertexBuffer = nullptr;
        }
        if (m_indexBuffer)
        {
            m_indexBuffer->Release();
            m_indexBuffer = nullptr;
        }
    }

    void CModel::RenderBuffers(ID3D11DeviceContext *deviceContext)
    {
        const uint32_t vertexBufferStride = static_cast<uint32_t>(sizeof(Vertex_s));
        const uint32_t vertexBufferOffset = 0;

        deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexBufferStride, &vertexBufferOffset);

        deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

} // namespace GP
