#pragma once

#include "stdafx.h"
#include "Circle.h"
#include "b2Object.h"

class Cb2Circle : public CCircle, public Cb2Object
{
public:
	Cb2Circle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, float radius, float density, float angle);
	~Cb2Circle();

	void SetPosition(glm::vec2 position) override;

	void SetSize(float size);

	void SetData(unsigned id);

	unsigned GetData() const;

	void ApplyImpulse(glm::vec2 direction) override;

private:
	b2CircleShape m_shape;
	b2FixtureDef m_fixture;
	b2BodyDef m_bdef;
	b2Body * m_body = nullptr;
	std::shared_ptr<b2World> m_world;
};
