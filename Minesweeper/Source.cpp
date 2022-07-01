#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Game.h"
#include "CellType.h"
#include "Grid.h"

int main()
{
    std::unordered_map<CellType, sf::Texture> gridTextures;

    for (int i = CellType::empty; i <= CellType::bombCross; i++)
    {
        sf::Texture texture;
        texture.loadFromFile("assets/minesweeper_" + std::to_string(i) + ".png");
        gridTextures[static_cast<CellType>(i)] = texture;
    }
    
    std::unique_ptr<IGameEntity> grid = std::make_unique<Grid>(gridTextures);

    Game game;
    game.attachEntity(grid);

    while (game.isRunning())
    {
        game.update();

        game.render();
    }

    return 0;
}