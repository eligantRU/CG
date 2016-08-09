#include "stdafx.h"
#include "Factory.h"

CFactory::CFactory(std::shared_ptr<b2World> world)
	:m_world(world)
{

}

CFactory::~CFactory() = default;

std::unique_ptr<Cb2Rectangle> CFactory::CreateRectangle(b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float weight, float angle)
{
	auto pObj = std::make_unique<Cb2Rectangle>(m_world, bodyType, position, size, weight, angle);
	pObj->SetData(m_counter++);
	return pObj;
};

std::unique_ptr<Cb2Circle> CFactory::CreateCircle(b2BodyType bodyType, glm::vec2 position, float radius, float weight, float angle)
{
	auto pObj = std::make_unique<Cb2Circle>(m_world, bodyType, position, radius, weight, angle);
	pObj->SetData(m_counter++);
	return pObj;
};
