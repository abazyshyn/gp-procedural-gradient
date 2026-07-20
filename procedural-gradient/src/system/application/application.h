#pragma once

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "direct3d/direct3d.h"
#include "model/model.h"
#include "camera/camera.h"
#include "shaders/pgradient_shader.h"

namespace GP
{
    /////////////
    // GLOBALS //
    /////////////
    constexpr bool FULL_SCREEN = false;
    constexpr bool SHOW_CURSOR = true;
    constexpr bool VSYNC_ENABLED = true;
    constexpr float FAR_PLANE = 1000.0f;
    constexpr float NEAR_PLANE = 0.3f;

    class CApplication
    {
    public:
        bool Init(int32_t windowWidth, int32_t windowHeight, HWND hWnd);
        void Shutdown();
        bool Frame();

    private:
        bool Render(float rotation);

    private:
        CDirect3D m_Direct3D;
        CModel m_Model;
        CCamera m_Camera;
        CPGradientShader m_PGradientShader;
    };

} // namespace GP
