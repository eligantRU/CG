#pragma once

#include "stdafx.h"
#include "PhysicalObject.h"
#include "B2Rectangle.h"
#include "B2Circle.h"

class CFactory
{
public:
	CFactory(std::shared_ptr<b2World> world)
		:m_world(world)
	{

	}

	~CFactory() = default;

	auto CreateRectangle(b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float weight, float angle)
	{
		auto pObj = std::make_unique<Cb2Rectangle>(m_world, bodyType, position, size, weight, angle);
		pObj->SetData(m_counter++);
		return pObj;
	}; 
	
	auto CreateCircle(b2BodyType bodyType, glm::vec2 position, float radius, float weight, float angle)
	{
		auto pObj = std::make_unique<Cb2Circle>(m_world, bodyType, position, radius, weight, angle);
		pObj->SetData(m_counter++);
		return pObj;
	};

private:
	std::shared_ptr<b2World> m_world;
	unsigned m_counter = 0;
};
