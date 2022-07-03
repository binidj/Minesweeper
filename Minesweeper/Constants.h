#pragma once
#include <SFML/Graphics.hpp>

// Collum amount
static const int MAX_GRID_COLLUMS = 12;
// Row amount
static const int MAX_GRID_ROWS = 12;

// Dimensions in pixel of a single cell
static const int CELL_SIZE = 32;

// Vertical, horizontal and diagonal grid directions.
static const std::vector<sf::Vector2i> directions = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

static const int SCREEN_WIDTH = 512;
static const int SCREEN_HEIGHT = 512;
static const int FRAME_RATE_LIMIT = 60;
static const int BOMBS_AMOUNT = 20;
