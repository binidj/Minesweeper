#pragma once

#include "IGameEntity.h"
#include "CellType.h"

/// <summary>
///     Wraps game logic information and sprite of a single cell. 
/// </summary>
struct Cell
{
	/// <summary>
	///     The cell's game state.
	/// </summary>
	CellType cellState; 
	
	/// <summary>
	///     Defines which texture to render.
	/// </summary>
	CellType cellRenderMode;

	sf::Sprite sprite;

	/// <summary>
	///     Shows whether a cell has a flag or not.
	/// </summary>
	bool hasBanner;

	/// <summary>
	///     Shows whether a cell has been clicked or not.
	/// </summary>
	bool isRevealed;

	Cell();

	void setSpriteTexture(const sf::Texture& texture);

	void resetCell();
};

