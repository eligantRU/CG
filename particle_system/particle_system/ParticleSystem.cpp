#include "stdafx.h"
#include "ParticleSystem.h"
#include "consts.h"

namespace
{

const glm::vec3 RED_COLOUR = { 1.f, 0.f, 0.f };
const glm::vec3 BLUE_COLOUR = { 0.f, 0.f, 1.f };

const float K = 500.f;
const float PARTICLE_WEIGHT = 1.f;

int Sign(float num)
{
	return (num > 0) - (num < 0);
}

glm::vec2 CalculateAcceleration(glm::vec2 pos1, glm::vec2 pos2, float charge1, float charge2, float minDistance)
{
	const float distance = glm::length(pos1 - pos2);

	if (distance <= minDistance)
	{
		return glm::vec2();
	}

	const float accelerationValue = (K / PARTICLE_WEIGHT) * fabs(charge1) * fabs(charge2) / pow(distance, 2);
	const float multiplier = (Sign(charge1) == Sign(charge2)) ? -1.f : 1.f;
	const glm::vec2 acceleration = multiplier * accelerationValue * -glm::normalize(pos2 - pos1);

	return acceleration;
}

}

CParticle::CParticle()
{
	SetElectricalCharge(0);
	SetPosition({ 0, 0 });
	SetVelocity({ 0, 0 });
	SetAcceleration({ 0, 0 });
}

CParticle::~CParticle() = default;

void CParticle::SetVelocity(const glm::vec2 & velocity)
{
	m_velocity = velocity;
}

glm::vec2 CParticle::GetVelocity() const
{
	return m_velocity;
}

CParticleEmitter::CParticleEmitter() = default;

CParticleEmitter::~CParticleEmitter() = default;

std::unique_ptr<CParticle> CParticleEmitter::Emit(float charge, glm::vec2 position)
{
	auto pParticle = std::make_unique<CParticle>();

	pParticle->SetElectricalCharge(charge);
	pParticle->SetPosition(position);
	pParticle->SetVelocity({ 0, 0 });
	pParticle->SetAcceleration({ 0, 0 });
	if (charge < 0)
	{
		pParticle->SetColor(BLUE_COLOUR);
	}
	else
	{
		pParticle->SetColor(RED_COLOUR);
	}
	return pParticle;
}

CParticleSystem::CParticleSystem() = default;
CParticleSystem::~CParticleSystem() = default;

void CParticleSystem::SetEmitter(std::unique_ptr<CParticleEmitter> && pEmitter)
{
	m_pEmitter = std::move(pEmitter);
}

void CParticleSystem::Advance(float dt)
{
	for (unsigned i = 0; i < m_particles.size(); ++i)
	{
		for (unsigned j = 0; j < m_particles.size(); ++j)
		{
			if (i == j)
			{
				continue;
			}

			auto acceleration = CalculateAcceleration(m_particles[i]->GetPosition(), m_particles[j]->GetPosition(), 
													  m_particles[i]->GetElectricalCharge(), m_particles[j]->GetElectricalCharge(),
													  m_particles[i]->GetRadius() + m_particles[j]->GetRadius());
			m_particles[j]->SetAcceleration(m_particles[j]->GetAcceleration() + acceleration);
		}
	}

	for (const auto &pParticle : m_particles)
	{
		pParticle->SetVelocity(pParticle->GetVelocity() + dt * pParticle->GetAcceleration());
		pParticle->SetPosition(pParticle->GetPosition() + dt * pParticle->GetVelocity());
	}

	auto newEnd = std::remove_if(m_particles.begin(), m_particles.end(), [](const auto &pParticle) {
		auto position = pParticle->GetPosition();
		return !(position.x + PARTICLE_RADUIS >= 0 && position.x - PARTICLE_RADUIS <= WINDOW_SIZE.x &&
			     position.y + PARTICLE_RADUIS >= 0 && position.y - PARTICLE_RADUIS <= WINDOW_SIZE.y);
	});
	m_particles.erase(newEnd, m_particles.end());
}

void CParticleSystem::Draw()
{
	for (const auto &pParticle : m_particles)
	{
		pParticle->Draw();
	}
}

void CParticleSystem::AddParticle(float charge, glm::vec2 position)
{
	m_particles.emplace_back(m_pEmitter->Emit(charge, position));
}

void CParticleSystem::Clear()
{
	m_particles.clear();
}
