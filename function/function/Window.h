#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

private:
    void SetupView(const glm::ivec2 &size);
    void DrawShapes();

    float m_time = 0.f;
};
