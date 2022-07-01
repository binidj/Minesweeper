#include "Grid.h"

Grid::Grid(std::unordered_map<CellType, sf::Texture>& gridTextures) : gridTextures(gridTextures)
{
	initCellTextures();
}

void Grid::initCellTextures()
{
	anchorPoint.x = 100.f;
	anchorPoint.y = 100.f;

	for (int i = 0; i < MAX_GRID_ROWS; i++)
	{
		for (int j = 0; j < MAX_GRID_COLLUMS; j++)
		{
			sf::Vector2f pos(anchorPoint.x + static_cast<float>(CELL_SIZE * i), anchorPoint.y + static_cast<float>(CELL_SIZE * j));
			grid[i][j].sprite.setPosition(pos);
			sf::Texture& texture = gridTextures[grid[i][j].cellRenderMode];
			grid[i][j].setSpriteTexture(texture);
		}
	}
}

void Grid::handleEvent(sf::Event& event)
{
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
