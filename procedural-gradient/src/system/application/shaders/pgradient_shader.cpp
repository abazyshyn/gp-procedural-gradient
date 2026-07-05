#include "pch.h"

#include "pgradient_shader.h"

namespace GP
{

    CPGradientShader::CPGradientShader()
        : m_vertexShader(nullptr),
          m_pixelShader(nullptr),
          m_inputLayout(nullptr),
          m_matrixBuffer(nullptr)
    {
    }

    bool CPGradientShader::Init(ID3D11Device *device, HWND hWnd)
    {
        const std::filesystem::path vsFilename{std::filesystem::current_path() / "res/shaders/pgradient_vs.hlsl"};
        const std::filesystem::path psFilename{std::filesystem::current_path() / "res/shaders/pgradient_ps.hlsl"};

        if (!InitShader(device, hWnd, vsFilename, psFilename))
        {
            return false;
        }

        return true;
    }

    void CPGradientShader::Shutdown()
    {
        ShutdownShader();
    }

    bool CPGradientShader::InitShader(ID3D11Device *device, HWND hWnd, const std::filesystem::path &vsFilename, const std::filesystem::path &psFilename)
    {
        ID3D10Blob *errorMessage = nullptr;
        ID3D10Blob *vertexShaderBuffer = nullptr;
        ID3D10Blob *pixelShaderBuffer = nullptr;

        if (FAILED(D3DCompileFromFile(vsFilename.c_str(), nullptr, nullptr, "PGradientVertexShader", "vs_5_0",
                                      D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage)))
        {
            if (errorMessage)
            {
                OutputShaderErrorMessage(errorMessage, hWnd, vsFilename);
            }
            else
            {
                MessageBox(hWnd, std::filesystem::absolute(vsFilename).c_str(), L"Missing Vertex Shader File", MB_OK);
            }

            return false;
        }

        if (FAILED(D3DCompileFromFile(psFilename.c_str(), nullptr, nullptr, "PGradientPixelShader", "vs_5_0",
                                      D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage)))
        {
            if (errorMessage)
            {
                OutputShaderErrorMessage(errorMessage, hWnd, vsFilename);
            }
            else
            {
                MessageBox(hWnd, std::filesystem::absolute(vsFilename).c_str(), L"Missing Vertex Shader File", MB_OK);
            }

            return false;
        }

        if (FAILED(device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &m_vertexShader)))
        {
            return false;
        }

        if (FAILED(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &m_pixelShader)))
        {
            return false;
        }

        std::array<D3D11_INPUT_ELEMENT_DESC, 2> polygonLayout{};
        polygonLayout[0].SemanticName = "POSITION";
        polygonLayout[0].SemanticIndex = 0;
        polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        polygonLayout[0].InputSlot = 0;
        polygonLayout[0].AlignedByteOffset = 0;
        polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[0].InstanceDataStepRate = 0;

        polygonLayout[1].SemanticName = "COLOR";
        polygonLayout[1].SemanticIndex = 0;
        polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        polygonLayout[1].InputSlot = 0;
        polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        polygonLayout[1].InstanceDataStepRate = 0;

        uint32_t elementsCount = static_cast<uint32_t>(polygonLayout.size());

        if (FAILED(device->CreateInputLayout(polygonLayout.data(), elementsCount, vertexShaderBuffer->GetBufferPointer(),
                                             vertexShaderBuffer->GetBufferSize(), &m_inputLayout)))
        {
            return false;
        }

        vertexShaderBuffer->Release();
        vertexShaderBuffer = nullptr;
        pixelShaderBuffer->Release();
        pixelShaderBuffer = nullptr;

        D3D11_BUFFER_DESC matrixBufferDescription{};
        matrixBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
        matrixBufferDescription.ByteWidth = sizeof(MatrixBuffer_s);
        matrixBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        matrixBufferDescription.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
        matrixBufferDescription.MiscFlags = 0;
        matrixBufferDescription.StructureByteStride = 0;

        if (FAILED(device->CreateBuffer(&matrixBufferDescription, nullptr, &m_matrixBuffer)))
        {
            return false;
        }

        return true;
    }

    void CPGradientShader::ShutdownShader()
    {
        if (m_vertexShader)
        {
            m_vertexShader->Release();
            m_vertexShader = nullptr;
        }
        if (m_pixelShader)
        {
            m_pixelShader->Release();
            m_pixelShader = nullptr;
        }
        if (m_inputLayout)
        {
            m_inputLayout->Release();
            m_inputLayout = nullptr;
        }
        if (m_matrixBuffer)
        {
            m_matrixBuffer->Release();
            m_matrixBuffer = nullptr;
        }
    }

    bool CPGradientShader::SetShaderMatrixBuffer(ID3D11DeviceContext *deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource{};

        if (FAILED(deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
        {
            return false;
        }

        MatrixBuffer_s *matrixBufferData = static_cast<MatrixBuffer_s *>(mappedResource.pData);
        matrixBufferData->worldMatrix = XMMatrixTranspose(worldMatrix);
        matrixBufferData->viewMatrix = XMMatrixTranspose(viewMatrix);
        matrixBufferData->projectionMatrix = XMMatrixTranspose(projectionMatrix);

        deviceContext->Unmap(m_matrixBuffer, 0);

        constexpr uint32_t matrixBufferPosition = 0;

        deviceContext->VSSetConstantBuffers(matrixBufferPosition, 1, &m_matrixBuffer);

        return true;
    }

} // namespace GP
