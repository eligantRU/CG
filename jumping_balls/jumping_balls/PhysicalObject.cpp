#pragma once

#include "stdafx.h"
#include "PhysicalObject.h"

void CPhysicalObject::SetPosition(glm::vec2 position)
{
	m_position = position;
}

glm::vec2 CPhysicalObject::GetPosition() const
{
	return m_position;
}

void CPhysicalObject::SetRotation(float angle)
{
	m_angle = angle;
}

float CPhysicalObject::GetRotation() const
{
	return m_angle;
}

void CPhysicalObject::SetDensity(float density)
{
	m_density = density;
}

float CPhysicalObject::GetDensity() const
{
	return m_density;
}

void CPhysicalObject::SetSize(glm::vec2 size)
{
	m_size = size;
}

glm::vec2 CPhysicalObject::GetSize() const
{
	return m_size;
}

void CPhysicalObject::SetData(unsigned id)
{
	m_id = id;
}

unsigned CPhysicalObject::GetData() const
{
	return m_id;
}
