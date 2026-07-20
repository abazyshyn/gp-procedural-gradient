#pragma once

namespace GP
{

    class CCamera
    {
    public:
        CCamera();

        void Render();

        void SetPosition(float x, float y, float z) { m_position = XMFLOAT3(x, y, z); }
        void SetRotation(float x, float y, float z) { m_rotation = XMFLOAT3(x, y, z); }

        void GetViewMatrix(XMMATRIX &viewMatrix) const { viewMatrix = m_viewMatrix; }
        XMFLOAT3 GetPosition() const { return m_position; }
        XMFLOAT3 GetRotation() const { return m_rotation; }

    private:
        XMMATRIX m_viewMatrix;
        XMFLOAT3 m_position;
        XMFLOAT3 m_rotation;

        unsigned char _padding[8] = {};
    };

} // namespace GP
