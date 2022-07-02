#pragma once

#include "IGameEntity.h"
#include "Cell.h"
#include "Constants.h"
#include <random>
#include <unordered_map>

class Grid : public IGameEntity
{
private:
	sf::Vector2f lowerAnchorPoint;
	sf::Vector2f upperAnchorPoint;
	Cell grid[MAX_GRID_ROWS][MAX_GRID_COLLUMS];
	std::unordered_map<CellType, sf::Texture> &gridTextures;
	void initCellTextures();
	void setBombsCoordinates();
	void initCellStates();
	void setSurroudingBombs();
	bool insideGrid(int x, int y);
public:
	Grid(std::unordered_map<CellType, sf::Texture>& gridTextures);
	void handleEvent(sf::Event& event);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

