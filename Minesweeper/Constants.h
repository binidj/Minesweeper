#pragma once
#include <SFML/Graphics.hpp>

// Grid
static const int MAX_GRID_COLLUMS = 12;
static const int MAX_GRID_ROWS = 12;
static const int CELL_SIZE = 32;
static const std::vector<sf::Vector2i> directions = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

// Game
static const int FRAME_RATE_LIMIT = 60;
static const int BOMBS_AMOUNT = 20;
