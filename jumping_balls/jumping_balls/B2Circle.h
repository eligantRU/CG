#pragma once

#include "stdafx.h"
#include "Circle.h"

class Cb2Circle : public CCircle
{
public:
	Cb2Circle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, float radius, float weight, float angle)
		:m_world(world)
	{
		Cb2Circle::SetPosition(position);
		Cb2Circle::SetWeight(weight);
		CCircle::SetRadius(radius);

		m_shape.m_radius = radius;
		m_bdef.type = bodyType; 
		m_bdef.angle = angle;

		m_bdef.position.Set(position.x, position.y);

		m_body = m_world->CreateBody(&m_bdef);
		m_body->CreateFixture(&m_shape, weight);
		m_body->SetBullet(false);
	}

	~Cb2Circle() = default;

	void SetPosition(glm::vec2 position)
	{
		CCircle::SetPosition(position); 
		m_bdef.position.Set(position.x, position.y);
	}

	void SetSize(float size)
	{
		CCircle::SetSize({ size, size });
		CCircle::SetRadius(size);
		m_shape.m_radius = size;
	}


	void SetData(unsigned id)
	{
		CPhysicalObject::SetData(id);
		m_body->SetUserData((void*)id);
	}

	unsigned GetData() const
	{
		return CPhysicalObject::GetData();
	}

private:
	b2CircleShape m_shape;
	b2BodyDef m_bdef;
	b2Body * m_body; // TODO: fix memory leak
	std::shared_ptr<b2World> m_world;
};
