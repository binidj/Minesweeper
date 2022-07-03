#pragma once

#include "IGameEntity.h"
#include "Cell.h"
#include "Constants.h"
#include "Button.h"
#include <random>
#include <unordered_map>

class Grid : public IGameEntity
{
private:
	sf::Vector2f lowerAnchorPoint;
	sf::Vector2f upperAnchorPoint;
	sf::Vector2f mousePosition;
	sf::Vector2i gridPosition;
	Cell grid[MAX_GRID_COLLUMS][MAX_GRID_ROWS];
	std::unordered_map<CellType, sf::Texture> &gridTextures;
	int unrevealedCells;
	bool listeningInput;

	void initGridPosition();
	void initCellTextures();
	void setBombsCoordinates();
	void initCellStates();
	void setSurroudingBombs();
	void revealCell();
	void toggleBanner();
	void handleGameLost();
	void handleGameWon();
	void resetCells();
	void applyTextureToCell(CellType cellTexture, Cell& cell);
	void propagateReveal(int col, int row);
	sf::Vector2i calcGridPosition();
	bool mouseInsideGrid();
	bool isValidGridCell(int col, int row);

public:
	Grid(std::unordered_map<CellType, sf::Texture>& gridTextures, sf::Vector2f lowerAnchorPoint);
	void resetGrid();
	void handleEvent(sf::Event& event);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

