#include "pch.h"

#include "model.h"

namespace GP
{

    CModel::CModel()
        : m_vertexBuffer(nullptr),
          m_indexBuffer(nullptr),
          m_vertexCount(0),
          m_indexCount(0),
          m_rgbPosition(0)
    {
    }

    bool CModel::Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext, std::string modelFilename)
    {
        if (!LoadModel(modelFilename))
        {
            return false;
        }

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
        std::vector<Vertex_s> vertices(static_cast<size_t>(m_vertexCount));
        std::vector<uint32_t> indices(static_cast<size_t>(m_indexCount));
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            vertices[i].position = XMFLOAT3(m_modelData[i].x, m_modelData[i].y, m_modelData[i].z);
            indices[i] = static_cast<uint32_t>(i);
        }

        D3D11_BUFFER_DESC vertexBufferDescription{};
        vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
        vertexBufferDescription.ByteWidth = static_cast<uint32_t>(vertices.size()) * static_cast<uint32_t>(sizeof(Vertex_s));
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
        indexBufferDescription.ByteWidth = static_cast<uint32_t>(indices.size()) * sizeof(uint32_t);
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

    bool CModel::LoadModel(std::string modelFilename)
    {
        std::filesystem::path modelFilepath{std::filesystem::current_path() / "res" / "models" / modelFilename};

        std::ifstream fin;
        fin.open(modelFilepath);
        if (!fin.is_open())
        {
            return false;
        }

        char input{};
        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }

        fin >> m_vertexCount;
        m_indexCount = m_vertexCount;

        m_modelData.resize(m_vertexCount);

        fin.get(input);
        while (input != ':')
        {
            fin.get(input);
        }
        fin.get(input);
        fin.get(input);

        for (Model_s &data : m_modelData)
        {
            fin >> data.x >> data.y >> data.z;
            fin >> data.tu >> data.tv;
            fin >> data.nx >> data.ny >> data.nz;
        }

        fin.close();

        return true;
    }

} // namespace GP
