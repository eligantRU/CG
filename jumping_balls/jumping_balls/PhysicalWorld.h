#pragma once

#include "stdafx.h"
#include "World.h"
#include "PhysicalObject.h"
#include "Factory.h"

class CPhysicalWorld : public CWorld
{
public:
	CPhysicalWorld(glm::vec2 gravity);
	~CPhysicalWorld() = default;
	void Draw() const;
	// void Add(); // TODO: does it need to be a private?

private:
	std::shared_ptr<b2World> m_world;
	std::vector<std::unique_ptr<CPhysicalObject>> m_objects;
	std::unique_ptr<CFactory> m_factory;
};
