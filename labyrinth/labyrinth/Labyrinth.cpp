#include "stdafx.h"

#include "Labyrinth.h"

CLabyrinth::CLabyrinth() = default;

CLabyrinth::~CLabyrinth() = default;

void CLabyrinth::Draw() const
{
	for (const auto bla : m_labyrinth) // TODO: no bla
	{
		for (const auto bla : bla) // TODO: no bla
		{
			bla.Draw();
		}
	}
}
