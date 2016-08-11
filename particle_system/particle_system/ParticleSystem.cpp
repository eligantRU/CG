#include "stdafx.h"
#include "consts.h"
#include "ParticleSystem.h"

namespace
{

const float K = 90'000'000.f;
const float PARTICLE_WEIGHT = 900'000'000.f;

int Sign(float num)
{
	return (num > 0) - (num < 0);
}

glm::vec2 CalculateAccelerationByAngle(float acceleration, float dx, float dy, float angle)
{
	glm::vec2 accelerat = { 0, 0 };
	if (dx >= 0 && dy >= 0)
	{
		accelerat = { -fabs(acceleration) * sin(M_PI / 2 - angle), -fabs(acceleration) * cos(M_PI / 2 - angle) };
	}
	else if (dx >= 0 && dy <= 0)
	{
		accelerat = { fabs(acceleration) * sin(angle), fabs(acceleration) * cos(angle) };
	}
	else if (dx <= 0 && dy >= 0)
	{
		accelerat = { -fabs(acceleration) * sin(angle - M_PI / 2), -fabs(acceleration) * cos(angle - M_PI / 2) };
	}
	else if (dx <= 0 && dy <= 0)
	{
		accelerat = { fabs(acceleration) * sin(angle + M_PI / 2), fabs(acceleration) * cos(angle + M_PI / 2) };
	}

	return accelerat;
}

glm::vec2 CalculateAccelerationByCharge(glm::vec2 accelerat, float charge1, float charge2)
{
	if (Sign(charge1) == Sign(charge2))
	{
		accelerat *= -1;
	}

	return accelerat;
}

glm::vec2 CalculateAcceleration(glm::vec2 pos1, glm::vec2 pos2, float charge1, float charge2)
{
	auto posI = pos1;
	auto posJ = pos2;
	float r = sqrt(pow(posI.x - posJ.x, 2) + pow(posI.y - posJ.y, 2));
	r = r ? r : 0.000001f;
	float acceleration = (K / PARTICLE_WEIGHT) * fabs(charge1) * fabs(charge2) / pow(r, 2);
	auto a = posJ.x - posI.x;
	auto b = posJ.y - posI.y;
	auto alpha = asin(b / r);
	glm::vec2 accelerat = CalculateAccelerationByAngle(acceleration, a, b, alpha);
	accelerat = CalculateAccelerationByCharge(accelerat, charge1, charge2);

	return accelerat;
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
	const glm::vec3 RED = { 1.f, 0.f, 0.f };
	const glm::vec3 BLUE = { 0.f, 0.f, 1.f };

	auto pParticle = std::make_unique<CParticle>();

	pParticle->SetElectricalCharge(charge);
	pParticle->SetPosition(position);
	pParticle->SetVelocity({ 0, 0 });
	pParticle->SetAcceleration({ 0, 0 });
	if (charge < 0)
	{
		pParticle->SetColor(BLUE);
	}
	else
	{
		pParticle->SetColor(RED);
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
													  m_particles[i]->GetElectricalCharge(), m_particles[j]->GetElectricalCharge());
			m_particles[j]->SetAcceleration(m_particles[j]->GetAcceleration() + acceleration);
		}
	}

	auto newEnd = std::remove_if(m_particles.begin(), m_particles.end(), [](const auto &pParticle) {
		auto position = pParticle->GetPosition();
		return !(position.x >= 0 && position.x <= WINDOW_SIZE.x && position.y >= 0 && position.y <= WINDOW_SIZE.y); 
	});
	m_particles.erase(newEnd, m_particles.end());

	for (const auto &pParticle : m_particles)
	{
		pParticle->SetVelocity(pParticle->GetVelocity() + dt * pParticle->GetAcceleration());
		pParticle->SetPosition(pParticle->GetPosition() + pParticle->GetVelocity());
	}
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
