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

	for (int i = 0; i < MAX_GRID_ROWS; i++)
	{
		for (int j = 0; j < MAX_GRID_COLLUMS; j++)
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
	std::vector<int> bombs(MAX_GRID_COLLUMS * MAX_GRID_ROWS);
	std::fill(bombs.begin(), bombs.begin() + BOMBS_AMOUNT, 1);

	std::shuffle(bombs.begin(), bombs.end(), rng);

	int index = 0;

	for (int i = 0; i < MAX_GRID_ROWS; i++)
	{
		for (int j = 0; j < MAX_GRID_COLLUMS; j++)
		{
			if (bombs[index++] != 0)
				grid[i][j].cellState = CellType::bomb;
		}
	}
}

void Grid::setSurroudingBombs()
{
	for (int i = 0; i < MAX_GRID_ROWS; i++)
	{
		for (int j = 0; j < MAX_GRID_COLLUMS; j++)
		{
			if (grid[i][j].cellState == CellType::bomb) continue;
			
			int surroundingBombs = 0;

			for (auto& dir : directions)
			{
				surroundingBombs += grid[i + dir.x][j + dir.y].cellState == CellType::bomb;
			}

			grid[i][j].cellState = static_cast<CellType>(surroundingBombs);

			// grid[i][j].cellRenderMode = grid[i][j].cellState;
		}
	}
}



void Grid::initCellStates()
{
	setBombsCoordinates();
	
	setSurroudingBombs();
}

bool Grid::insideGrid(int x, int y)
{
	//float fx = static_cast<float>(x);
	//float fy = static_cast<float>(y);
}

void Grid::handleEvent(sf::Event& event)
{
	
	//if (event.type == sf::Event::MouseButtonPressed)
	//{
	//	std::cout << event.mouseButton.button << " !!!\n";
	//	std::cout << event.mouseButton.x << " " << event.mouseButton.y << " !!!\n";
	//	if (insideGrid(x, y))
	//		return;

	//	//if (event.mouseButton.button == sf::Mouse::Button::Left)
	//		//revealCell();

	//	//if (event.mouseButton.button == sf::Mouse::Button::Left)
	//		//placeBanner();
	//	
	//}
}

void Grid::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	for (int i = 0; i < MAX_GRID_ROWS; i++)
	{
		for (int j = 0; j < MAX_GRID_COLLUMS; j++)
		{
			window->draw(grid[i][j].sprite);
		}
	}
}
