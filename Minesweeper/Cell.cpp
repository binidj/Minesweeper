#include "Cell.h"

Cell::Cell()
{
	resetCell();
}

void Cell::setSpriteTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void Cell::resetCell()
{
	cellState = CellType::empty;
	cellRenderMode = CellType::unrevealed;
	hasBanner = false;
	isRevealed = false;
}
