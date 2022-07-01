#pragma once

#include "IGameEntity.h"
#include "CellType.h"

struct Cell
{
	CellType cellState;
	CellType cellRenderMode;
	sf::Sprite sprite;
	bool hasBanner;
	bool isRevealed;
	Cell();
	void setSpriteTexture(const sf::Texture& texture);
};

