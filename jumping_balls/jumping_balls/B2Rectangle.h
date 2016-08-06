#pragma once

#include "stdafx.h"
#include "Rectangle.h"
#include "consts.h"

class Cb2Rectangle : public CRectangle
{
public:
	Cb2Rectangle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float weight, float angle)
	:m_world(world)
	{
		CRectangle::SetPosition(position);
		CRectangle::SetSize(size);
		CRectangle::SetWeight(weight);

		m_shape.SetAsBox(size.x, size.y);
		m_bdef.type = bodyType; 
		m_bdef.angle = angle;

		m_bdef.position.Set(position.x, position.y);
		
		m_body = m_world->CreateBody(&m_bdef);
		m_body->CreateFixture(&m_shape, weight);
		m_body->SetBullet(false);
	}

	~Cb2Rectangle() = default;

	void SetPosition(glm::vec2 position)
	{
		CRectangle::SetPosition(position);
		m_bdef.position.Set(position.x, position.y);
	}	
	
	void SetSize(glm::vec2 size)
	{
		CRectangle::SetSize(size);
		m_shape.SetAsBox(size.x, size.y);
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

	void ApplyImpulse(glm::vec2 direction) override
	{
		m_body->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), true);
	}

private:
	b2PolygonShape m_shape;
	b2BodyDef m_bdef;
	b2Body * m_body; // TODO: fix memory leak
	std::shared_ptr<b2World> m_world;
};
