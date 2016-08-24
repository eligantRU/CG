#pragma once

#include "stdafx.h"
#include "DispatchEvent.h"
#include "Camera.h"
#include "Lights.h"
#include "FunctionSurface.h"

struct SFunctionInfo
{
public:
	SFunctionInfo(const Function3D & fn, const glm::vec2 & rangeX, const glm::vec2 & rangeY, const float & step = 0.01f);
	~SFunctionInfo();

	Function3D GetFunction() const;
	glm::vec2 GetRangeX() const;
	glm::vec2 GetRangeY() const;
	float GetStep() const;

private:
	Function3D m_fn;
	glm::vec2 m_rangeX;
	glm::vec2 m_rangeY;
	float m_step;
};

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

protected:
    // CAbstractWindow interface
    void OnWindowInit(const glm::ivec2 & size) override;
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 & size) override;

    // IInputEventAcceptor interface
	void OnScroll(const int &) override;
	void OnDragBegin(const glm::vec2 & pos) override;
	void OnDragMotion(const glm::vec2 & pos) override;
	void OnDragEnd(const glm::vec2 & pos) override;
	void OnKeyUp(const SDL_KeyboardEvent & key) override;

private:
    void SetupView(const glm::ivec2 & size);

	CPhongModelMaterial m_material;
	CSolidFunctionSurface m_surface;
    CCamera m_camera;
	CDirectedLightSource m_sunlight;
	glm::vec2 m_dragPosition;
	bool m_lineMode = false;
	std::vector<SFunctionInfo> m_bla;
};
