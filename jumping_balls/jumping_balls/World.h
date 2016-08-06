#pragma once

#include "stdafx.h"

class CWorld : private boost::noncopyable
{
public:
	CWorld() = default;
	virtual ~CWorld() = default;

	virtual void Draw() const = 0;
	virtual void Fire(glm::vec2 direction) = 0;

private:
};
