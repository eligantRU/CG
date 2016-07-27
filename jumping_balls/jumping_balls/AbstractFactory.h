#pragma once

#include "stdafx.h"

template<class Base> class CAbstractFactory 
{
public:
	CAbstractFactory() = default;
	~CAbstractFactory() = default;

	template<class Derived> std::unique_ptr<Base> create()
	{
		return std::make_unique<Derived>();
	}

private:
};
