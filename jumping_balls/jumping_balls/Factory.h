#pragma once

#include "stdafx.h"
#include "PhysicalObject.h"
#include "B2Rectangle.h"
#include "B2Circle.h"

class CFactory
{
public:
	CFactory(std::shared_ptr<b2World> world);

	~CFactory();

	std::unique_ptr<Cb2Rectangle> CreateRectangle(b2BodyType bodyType, glm::vec2 position, glm::vec2 size, float density, float angle);
	
	std::unique_ptr<Cb2Circle> CreateCircle(b2BodyType bodyType, glm::vec2 position, float radius, float density, float angle);

private:
	std::shared_ptr<b2World> m_world;
	unsigned m_counter = 0;
};
