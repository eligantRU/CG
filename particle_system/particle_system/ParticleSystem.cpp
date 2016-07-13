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
}

void CParticle::SetVelocity(const glm::vec2 & velocity)
{
	m_velocity = velocity;
}

glm::vec2 CParticle::GetVelocity() const
{
	return m_velocity;
}

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
			auto posI = m_particles[i]->GetPosition();
			auto posJ = m_particles[j]->GetPosition();
			float r = sqrt(pow(posI.x - posJ.x, 2) + pow(posI.y - posJ.y, 2));
			r = r ? r : 0.000001f;
			float acceleration = (K / PARTICLE_WEIGHT) * fabs(m_particles[i]->GetElectricalCharge()) * fabs(m_particles[j]->GetElectricalCharge()) / pow(r, 2);
			auto c = r;
			auto a = posJ.x - posI.x;
			auto b = posJ.y - posI.y;
			auto alpha = asin(b / c); 
			glm::vec2 accelerat = { 0, 0 };
			if (a >= 0 && b >= 0)
			{
				accelerat = { -fabs(acceleration) * sin(M_PI / 2 - alpha), -fabs(acceleration) * cos(M_PI / 2 - alpha) };
			}
			else if (a >= 0 && b <= 0)
			{
				accelerat = { fabs(acceleration) * sin(alpha), fabs(acceleration) * cos(alpha) };
			}
			else if (a <= 0 && b >= 0)
			{
				accelerat = { -fabs(acceleration) * sin(alpha - M_PI / 2), -fabs(acceleration) * cos(alpha - M_PI / 2) };
			}
			else if (a <= 0 && b <= 0)
			{
				accelerat = { fabs(acceleration) * sin(alpha + M_PI / 2), fabs(acceleration) * cos(alpha + M_PI / 2) };
			}
			if (Sign(m_particles[i]->GetElectricalCharge()) == Sign(m_particles[j]->GetElectricalCharge()))
			{
				accelerat *= -1;
			}
			m_particles[j]->SetAcceleration(m_particles[j]->GetAcceleration() + accelerat);
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
