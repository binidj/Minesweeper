#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <Windows.h>
#include "Game.h"
#include "CellType.h"
#include "Grid.h"

int main()
{
    FreeConsole();
    
    // Maps a CellType to its respective texture
    std::unordered_map<CellType, sf::Texture> gridTextures;

    // Texture loading
    for (int i = CellType::empty; i <= CellType::bombCross; i++)
    {
        sf::Texture texture;
        texture.loadFromFile("assets/minesweeper_" + std::to_string(i) + ".png");
        gridTextures[static_cast<CellType>(i)] = texture;
    }
    
    // Game entities creation and attachment to the main game object

    Game game;
    
    std::unique_ptr<IGameEntity> grid = std::make_unique<Grid>(gridTextures, sf::Vector2f(65.f, 90.f));

    std::unique_ptr<IGameEntity> resetButton = std::make_unique<Button>(
        std::bind(&Grid::resetGrid, static_cast<Grid*>(grid.get())),
        sf::Vector2f(242.f, 30.f),
        32.f,
        32.f
    );

    game.attachEntity(resetButton);

    game.attachEntity(grid);
    
    // Game loop
    while (game.isRunning())
    {
        game.update();

        game.render();
    }

    return 0;
}