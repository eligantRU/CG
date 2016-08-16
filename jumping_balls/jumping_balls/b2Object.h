#pragma once

#include "stdafx.h"

class Cb2Object
{
public:
	Cb2Object() = default;
	~Cb2Object() = default;

	void SetPosition(glm::vec2 position) { (void)position; };

	void SetSize() { };

	void SetData(unsigned id) { (void)id; };

	unsigned GetData() const { };

	void ApplyImpulse(glm::vec2 direction) { (void)direction; };

private:
};
