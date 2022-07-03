#include "Grid.h"

Grid::Grid(std::unordered_map<CellType, sf::Texture>& gridTextures, sf::Vector2f lowerAnchorPoint) : 
	gridTextures(gridTextures), lowerAnchorPoint(lowerAnchorPoint)
{	
	resetGrid();
}

void Grid::resetGrid() 
{
	listeningInput = true;
	unrevealedCells = (MAX_GRID_COLLUMS * MAX_GRID_ROWS) - BOMBS_AMOUNT;

	resetCells();
	
	initGridPosition();

	initCellStates();

	initCellTextures();
}

void Grid::initGridPosition()
{
	upperAnchorPoint.x = lowerAnchorPoint.x + static_cast<float>(CELL_SIZE * MAX_GRID_COLLUMS);
	upperAnchorPoint.y = lowerAnchorPoint.y + static_cast<float>(CELL_SIZE * MAX_GRID_ROWS);
}

void Grid::initCellTextures()
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			sf::Vector2f pos(lowerAnchorPoint.x + static_cast<float>(CELL_SIZE * i), lowerAnchorPoint.y + static_cast<float>(CELL_SIZE * j));
			grid[i][j].sprite.setPosition(pos);
			applyTextureToCell(CellType::unrevealed, grid[i][j]);
		}
	}
}

void Grid::setBombsCoordinates()
{
	std::random_device device;
	std::mt19937 rng(device());
	std::vector<int> bombs(MAX_GRID_ROWS * MAX_GRID_COLLUMS);
	std::fill(bombs.begin(), bombs.begin() + BOMBS_AMOUNT, 1);

	std::shuffle(bombs.begin(), bombs.end(), rng);

	int index = 0;

	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			if (bombs[index++] != 0)
				grid[i][j].cellState = CellType::bomb;
		}
	}
}

void Grid::setSurroudingBombs()
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			if (grid[i][j].cellState == CellType::bomb) continue;
			
			int surroundingBombs = 0;

			for (auto& dir : directions)
			{
				if (isValidGridCell(i + dir.x, j + dir.y))
					surroundingBombs += grid[i + dir.x][j + dir.y].cellState == CellType::bomb;
			}

			grid[i][j].cellState = static_cast<CellType>(surroundingBombs);

			// grid[i][j].cellRenderMode = grid[i][j].cellState;
		}
	}
}

void Grid::applyTextureToCell(CellType cellTexture, Cell& cell)
{
	cell.cellRenderMode = cellTexture;
	sf::Texture& texture = gridTextures[cell.cellRenderMode];
	cell.setSpriteTexture(texture);
}

void Grid::propagateReveal(int col, int row)
{
	Cell& cell = grid[col][row];

	if (!isValidGridCell(col, row) || cell.isRevealed)
		return;

	unrevealedCells -= 1;
	cell.isRevealed = true;

	applyTextureToCell(cell.cellState, cell);

	if (cell.cellState == CellType::empty)
	{
		for (int i = 0; i < directions.size(); i++)
		{
			propagateReveal(col + directions[i].x, row + directions[i].y);
		}
	}
}

void Grid::revealCell()
{
	Cell& cell = grid[gridPosition.x][gridPosition.y];

	if (cell.hasBanner)
		return;

	if (cell.cellState == CellType::bomb)
	{
		listeningInput = false;
		// std::cout << "Hit bomb" << "\n";
		handleGameLost();
		return;
	}

	propagateReveal(gridPosition.x, gridPosition.y);

	if (unrevealedCells == 0)
	{
		listeningInput = false;
		// std::cout << "Game Won" << "\n";
		handleGameWon();
	}
}

void Grid::toggleBanner()
{
	Cell& cell = grid[gridPosition.x][gridPosition.y];

	if (cell.isRevealed)
		return;

	cell.hasBanner = !cell.hasBanner;

	if (cell.cellRenderMode == CellType::unrevealed)
		applyTextureToCell(CellType::banner, cell);
	else if (cell.cellRenderMode == CellType::banner)
		applyTextureToCell(CellType::unrevealed, cell);
}

void Grid::handleGameLost()
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			if (grid[i][j].cellState == CellType::bomb)
			{
				applyTextureToCell(CellType::bomb, grid[i][j]);
			}
		}
	}
}

void Grid::handleGameWon()
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			if (grid[i][j].cellState == CellType::bomb)
			{
				applyTextureToCell(CellType::bombCross, grid[i][j]);
			}
		}
	}
}

void Grid::resetCells()
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			grid[i][j].resetCell();
		}
	}
}

sf::Vector2i Grid::calcGridPosition()
{
	const float cellSize = static_cast<float>(CELL_SIZE);
	const int rowPosition = static_cast<int>(floor((mousePosition.x - lowerAnchorPoint.x) / cellSize));
	const int colPosition = static_cast<int>(floor((mousePosition.y - lowerAnchorPoint.y) / cellSize));
	return sf::Vector2i(rowPosition, colPosition);
}

void Grid::initCellStates()
{
	setBombsCoordinates();
	
	setSurroudingBombs();
}

bool Grid::mouseInsideGrid()
{
	return (mousePosition.x >= lowerAnchorPoint.x && mousePosition.y >= lowerAnchorPoint.y &&
			mousePosition.x <= upperAnchorPoint.x && mousePosition.y <= upperAnchorPoint.y);
}

bool Grid::isValidGridCell(int col, int row)
{
	return (col >= 0 && col < MAX_GRID_COLLUMS && row >= 0 && row < MAX_GRID_ROWS);
}

void Grid::handleEvent(sf::Event& event)
{
	
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (!listeningInput)
			return;
		
		mousePosition = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

		// std::cout << mousePosition.x << " " << mousePosition.y << " Mouse pos\n";
		
		if (!mouseInsideGrid())
			return;

		gridPosition = calcGridPosition();

		// std::cout << gridPosition.x << " " << gridPosition.y << " Grid pos\n";
		
		if (event.mouseButton.button == sf::Mouse::Button::Left)
			revealCell();

		if (event.mouseButton.button == sf::Mouse::Button::Right)
			toggleBanner();
	}
}

void Grid::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			window->draw(grid[i][j].sprite);
		}
	}
}
