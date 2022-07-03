#include "Grid.h"
#include <iostream>

Grid::Grid(std::unordered_map<CellType, sf::Texture>& gridTextures) : gridTextures(gridTextures)
{
	initCellStates();

	initCellTextures();
}

void Grid::initCellTextures()
{
	lowerAnchorPoint.x = 65.f;
	lowerAnchorPoint.y = 65.f;

	upperAnchorPoint.x = lowerAnchorPoint.x + static_cast<float>(CELL_SIZE * MAX_GRID_COLLUMS);
	upperAnchorPoint.y = lowerAnchorPoint.y + static_cast<float>(CELL_SIZE * MAX_GRID_ROWS);

	for (int i = 0; i < MAX_GRID_COLLUMS; i++)
	{
		for (int j = 0; j < MAX_GRID_ROWS; j++)
		{
			sf::Vector2f pos(lowerAnchorPoint.x + static_cast<float>(CELL_SIZE * i), lowerAnchorPoint.y + static_cast<float>(CELL_SIZE * j));
			grid[i][j].sprite.setPosition(pos);
			sf::Texture& texture = gridTextures[grid[i][j].cellRenderMode];
			grid[i][j].setSpriteTexture(texture);
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

void Grid::revealCell()
{
}

void Grid::placeBanner()
{
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
		mousePosition = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

		std::cout << mousePosition.x << " " << mousePosition.y << " Mouse pos\n";
		
		if (!mouseInsideGrid())
			return;

		gridPosition = calcGridPosition();

		std::cout << gridPosition.x << " " << gridPosition.y << " Grid pos\n";
		
		if (event.mouseButton.button == sf::Mouse::Button::Left)
			revealCell();

		if (event.mouseButton.button == sf::Mouse::Button::Right)
			placeBanner();
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
