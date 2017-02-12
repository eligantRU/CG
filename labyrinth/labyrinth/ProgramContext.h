#pragma once

#include "libchapter3.h"
#include "IProgramContext.h"

class CProgramContext
	:public IProgramContext
{
public:
	virtual ~CProgramContext() = default;

	CVertexAttribute GetPositionAttr() const override;
	CVertexAttribute GetNormalAttr() const override;
	CVertexAttribute GetTexCoordAttr() const override;

	const glm::mat4 & GetModel() const override;
	const glm::mat4 & GetView() const override;
	const glm::mat4 & GetProjection() const override;
	const SLightSource & GetLight0() const override;

	void SetModel(const glm::mat4 & value) override;
	void SetView(const glm::mat4 & value) override;
	void SetProjection(const glm::mat4 & value) override;
	void SetLight0(const SLightSource & source) override;

protected:
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_normalModelView;
	SLightSource m_light0;

	CShaderProgram m_program;
};
