#pragma once

#include "stdafx.h"

class CElectricalParticle : private boost::noncopyable
{
public:
	CElectricalParticle() = default;
	virtual ~CElectricalParticle();

	virtual void Draw() const;

	void SetElectricalCharge(float);
	float GetElectricalCharge();

	void SetColor(const glm::vec3 & ñolor);
	glm::vec3 GetColor() const;

	void SetPosition(const glm::vec2 &);
	const glm::vec2 & GetPosition() const;

	float GetRadius() const;

	virtual bool HitTest(const glm::vec2 & point) const;

private:
	void DeleteList();
	void Redraw() const;

	mutable unsigned m_displayList = 0;
	float m_electricalCharge = 0;
	glm::vec2 m_position;
	glm::vec3 m_color;
};
