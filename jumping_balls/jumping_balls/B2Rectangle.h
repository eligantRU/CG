#pragma once

#include "stdafx.h"
#include "Rectangle.h"
#include "b2Object.h"

class Cb2Rectangle : public CRectangle, public Cb2Object
{
public:
	Cb2Rectangle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float weight, float angle);
	~Cb2Rectangle();

	void SetPosition(glm::vec2 position) override;
	
	void SetSize(glm::vec2 size);

	void SetData(unsigned id);

	unsigned GetData() const;

	void ApplyImpulse(glm::vec2 direction) override;

private:
	b2PolygonShape m_shape;
	b2BodyDef m_bdef;
	b2Body * m_body; // TODO: fix memory leak
	std::shared_ptr<b2World> m_world;
};
