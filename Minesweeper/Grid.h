#pragma once

#include "IGameEntity.h"
#include "Cell.h"
#include "Constants.h"
#include "Button.h"
#include <random>
#include <unordered_map>

/// <summary>
///     Represents the Minesweeper grid, containing a matrix of <c> Cell </c>, managing grid initialization and player interaction. 
/// </summary>
class Grid : public IGameEntity
{
private:
	sf::Vector2f lowerAnchorPoint;

	sf::Vector2f upperAnchorPoint;

	sf::Vector2f mousePosition;

	sf::Vector2i gridPosition;

	Cell grid[MAX_GRID_COLLUMS][MAX_GRID_ROWS];

	/// <summary>
	///     Maps a CellType to its respective texture. 
	/// </summary>
	std::unordered_map<CellType, sf::Texture> &gridTextures;

	/// <summary>
	///     Represents how many cells the player has to reveal to win .
	/// </summary>
	int unrevealedCells;

	/// <summary>
	///     Wheather the class process the player input or not.
	/// </summary>
	bool listeningInput;

	void fixUpperAnchorPoint();

	void initCellTextures();

	/// <summary>
	///     Shuffles bombs on the grid.
	/// </summary>
	void setBombsCoordinates();
	
	void initCellStates();

	/// <summary>
	///     Defines all cell states of the grid depending on how many bombs surrounds each cell.
	/// </summary>
	void setSurroudingBombs();

	/// <summary>
	///     Reveals wheather a bomb or a empty cell lies inside the current cell.
	/// </summary>
	void revealCell();
	
	/// <summary>
	///     Places or unplaces a banner on the current cell.
	/// </summary>
	void toggleBanner();
	
	/// <summary>
	///     Defines grid behavior when the player loses the game.
	/// </summary>
	void handleGameLost();
	
	/// <summary>
	///     Defines grid behavior when the player wins the game.
	/// </summary>
	void handleGameWon();
	
	/// <summary>
	///     Clears all cells to its initial state
	/// </summary>
	void resetCells();
	
	/// <summary>
	///     Updates the texture of a cell
	/// </summary>
	/// <param name="cellTexture"> The cell texture to be set </param>
	/// <param name="cell"> The cell instance </param> 
	void applyTextureToCell(CellType cellTexture, Cell& cell);
	
	/// <summary>
	///     Recursively reveals nearby empty cells
	/// </summary>
	void propagateReveal(int col, int row);
	
	/// <summary>
	///     Calculates the grid position based on the current <c> mousePosition </c>
	/// </summary>
	sf::Vector2i calcGridPosition();
	
	/// <summary>
	///     Wheather the mouse is inside the grid or not.
	/// </summary>
	bool mouseInsideGrid();
	
	/// <summary>
	///     Checks if the cell's coordinates is inside the grid.
	/// </summary>
	/// <param name="col"> The grid column </param>
	/// <param name="row"> The grid row </param>
	bool isValidGridCell(int col, int row);
public:
	Grid(std::unordered_map<CellType, sf::Texture>& gridTextures, const sf::Vector2f& lowerAnchorPoint);
	
	/// <summary>
	///     Reset the grid to its initial state.
	/// </summary>
	void resetGrid();
	
	void handleEvent(sf::Event& event);
	
	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

