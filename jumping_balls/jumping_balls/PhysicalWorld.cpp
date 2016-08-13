#pragma once

#include "stdafx.h"
#include "PhysicalWorld.h"
#include "PhysicalObject.h"
#include "Rectangle.h"
#include "Factory.h"
#include "consts.h"

CPhysicalWorld::CPhysicalWorld(glm::vec2 gravity)
{
	m_world = std::make_unique<b2World>(b2Vec2(gravity.x, gravity.y)); 
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	m_factory = std::make_unique<CFactory>(m_world);
	m_objects.reserve(50);
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { 0, 0 }, { WINDOW_SIZE.x, 10 }, 1, 0));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { 0, 0 }, { 10, WINDOW_SIZE.y }, 1, 0));
    m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { WINDOW_SIZE.x, 0 }, { 10, WINDOW_SIZE.y }, 1, 0));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { 0 , 3 * WINDOW_SIZE.y / 4 }, { 500, 20 }, 1, float(M_PI / 8)));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { WINDOW_SIZE.x , WINDOW_SIZE.y / 2 }, { 500, 20 }, 1, float(-M_PI / 8)));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { 2 * WINDOW_SIZE.x / 5, 3 * WINDOW_SIZE.y / 5 }, { 40, 80 }, 1, float(M_PI / 4)));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { WINDOW_SIZE.x / 5, WINDOW_SIZE.y / 4 }, { 60, 100 }, 1, float(3 * M_PI / 4)));
	m_objects.emplace_back(m_factory->CreateRectangle(b2BodyType::b2_staticBody, { 4 * WINDOW_SIZE.x / 5, WINDOW_SIZE.y / 6 }, { 60, 60 }, 1, float(M_PI / 30)));
}

void CPhysicalWorld::Advance(float dt)
{
	(void)dt;
	m_world->Step(1.f / 60.f, 8, 3);

	for (auto it = m_world->GetBodyList(); it != 0; it = it->GetNext())
	{
		auto pos = it->GetPosition();
		auto angle = it->GetAngle();

		auto objectData = unsigned(it->GetUserData());
		auto objIter = std::find_if(m_objects.begin(), m_objects.end(), [objectData](auto &pObject) {
			return (pObject->GetData() == objectData);
		});
		if (objIter >= m_objects.begin() && objIter < m_objects.end())
		{
			auto i = std::distance(m_objects.begin(), objIter);
			m_objects[i]->SetRotation(angle);
			m_objects[i]->SetPosition({ pos.x, pos.y });
		}
		else
		{
			it->SetActive(false);
		}
	}

	auto newEnd = std::remove_if(m_objects.begin(), m_objects.end(), [](auto &pObject) {
		auto pos = pObject->GetPosition();
		return !(pos.x >= 0 && pos.x <= WINDOW_SIZE.x && pos.y >= 0 && pos.y <= WINDOW_SIZE.y);
	});
	m_objects.erase(newEnd, m_objects.end());
}

void CPhysicalWorld::Draw() const
{
	for (const auto &pOpbject : m_objects)
	{
		pOpbject->Draw();
	}
}

void CPhysicalWorld::Fire(glm::vec2 direction)
{
	m_objects.push_back(m_factory->CreateCircle(b2BodyType::b2_dynamicBody, GUN_POSITION, 5, 0.1f, 0));
	m_objects[m_objects.size() - 1]->ApplyImpulse(direction - GUN_POSITION);
}
