#pragma once

#include "libchapter3.h"

class IProgramContext
{
public:
	struct SLightSource
	{
		glm::vec4 position;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

	virtual void Use() = 0;
	virtual CVertexAttribute GetPositionAttr() const = 0;
	virtual CVertexAttribute GetNormalAttr() const = 0;
	virtual CVertexAttribute GetTexCoordAttr() const = 0;

	virtual const glm::mat4 & GetModel() const = 0;
	virtual const glm::mat4 & GetView() const = 0;
	virtual const glm::mat4 & GetProjection() const = 0;
	virtual const SLightSource & GetLight0() const = 0;

	virtual void SetModel(const glm::mat4 & value) = 0;
	virtual void SetView(const glm::mat4 & value) = 0;
	virtual void SetProjection(const glm::mat4 & value) = 0;
	virtual void SetLight0(const SLightSource & source) = 0;
};
