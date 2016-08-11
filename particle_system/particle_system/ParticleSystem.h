#pragma once

#include "stdafx.h"
#include "MovableElectricalParticle.h"

class CParticle : public CMovableElectricalParticle
{
public:
	CParticle();
	~CParticle();
	void SetVelocity(const glm::vec2 & velocity);
	glm::vec2 GetVelocity() const;
	
private:
	glm::vec2 m_velocity;
};

class CParticleEmitter
{
public:
	CParticleEmitter();
	~CParticleEmitter();

	std::unique_ptr<CParticle> Emit(float charge, glm::vec2 position);

private:
};

class CParticleSystem
{
public:
	CParticleSystem();
	~CParticleSystem();

	void Draw();
    void Advance(float dt);
	void AddParticle(float charge, glm::vec2 position);
	void Clear();

	void SetEmitter(std::unique_ptr<CParticleEmitter> && pEmitter);

private:
	std::unique_ptr<CParticleEmitter> m_pEmitter;
	std::vector<std::unique_ptr<CParticle>> m_particles;
};
