#include "Cell.h"

Cell::Cell() : cellState(CellType::empty), cellRenderMode(CellType::unrevealed), hasBanner(false), isRevealed(false)
{
}

void Cell::setSpriteTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}
