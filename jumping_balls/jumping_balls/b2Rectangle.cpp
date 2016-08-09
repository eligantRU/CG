#include "stdafx.h"
#include "B2Rectangle.h"

Cb2Rectangle::Cb2Rectangle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float weight, float angle)
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

Cb2Rectangle::~Cb2Rectangle() = default;

void Cb2Rectangle::SetPosition(glm::vec2 position)
{
	CRectangle::SetPosition(position);
	m_bdef.position.Set(position.x, position.y);
}

void Cb2Rectangle::SetSize(glm::vec2 size)
{
	CRectangle::SetSize(size);
	m_shape.SetAsBox(size.x, size.y);
}

void Cb2Rectangle::SetData(unsigned id)
{
	CPhysicalObject::SetData(id);
	m_body->SetUserData((void*)id);
}

unsigned Cb2Rectangle::GetData() const
{
	return CPhysicalObject::GetData();
}

void Cb2Rectangle::ApplyImpulse(glm::vec2 direction)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), true);
}
