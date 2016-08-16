#include "stdafx.h"
#include "B2Circle.h"

Cb2Circle::Cb2Circle(std::shared_ptr<b2World> world, b2BodyType bodyType, glm::vec2 position, float radius, float weight, float angle)
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
	m_body->SetBullet(false);

	m_fixture.density = weight;
	m_fixture.restitution = 0.8f;
	m_fixture.friction = 0;
	m_fixture.shape = &m_shape;
	m_body->CreateFixture(&m_fixture);
}

Cb2Circle::~Cb2Circle()
{
	m_body = nullptr;
}

void Cb2Circle::SetPosition(glm::vec2 position)
{
	CCircle::SetPosition(position);
	m_bdef.position.Set(position.x, position.y);
}

void Cb2Circle::SetSize(float size)
{
	CCircle::SetSize({ size, size });
	CCircle::SetRadius(size);
	m_shape.m_radius = size;
}

void Cb2Circle::SetData(unsigned id)
{
	CPhysicalObject::SetData(id);
	m_body->SetUserData((void*)id);
}

unsigned Cb2Circle::GetData() const
{
	return CPhysicalObject::GetData();
}

void Cb2Circle::ApplyImpulse(glm::vec2 direction)
{
	m_body->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), false);
}
