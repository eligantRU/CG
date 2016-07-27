#pragma once

#include "stdafx.h"

class CWorld : private boost::noncopyable
{
public:
	CWorld() = default;
	virtual ~CWorld() = default;

	virtual void Draw() const = 0;

private:
};
