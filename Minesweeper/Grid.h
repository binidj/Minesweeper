#pragma once

#include "IGameEntity.h"
#include "Cell.h"
#include "Constants.h"
#include <unordered_map>

class Grid : public IGameEntity
{
private:
	sf::Vector2f anchorPoint;
	Cell grid[MAX_GRID_ROWS][MAX_GRID_COLLUMS];
	std::unordered_map<CellType, sf::Texture> &gridTextures;
public:
	Grid(std::unordered_map<CellType, sf::Texture>& gridTextures);
	void initCellTextures();
	void handleEvent(sf::Event& event);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

