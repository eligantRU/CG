#pragma once

#include "stdafx.h"
#include "ElectricalParticle.h"

class CMovableElectricalParticle : public CElectricalParticle
{
public:
	CMovableElectricalParticle() = default;

	void Draw() const override;
	bool HitTest(const glm::vec2 & point) const override;

	void SetPosition(const glm::vec2 &);
	const glm::vec2 & GetPosition() const;

	void SetAcceleration(const glm::vec2 &);
	const glm::vec2 & GetAcceleration() const;
private:
	glm::vec2 m_position;
	glm::vec2 m_acceleration;
};
