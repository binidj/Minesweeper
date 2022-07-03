#include "Game.h"

void Game::initVariables()
{
    window = nullptr;
    videoMode = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::initWindow()
{
    window = std::make_unique<sf::RenderWindow>(videoMode, "Minesweeper");
    window->setFramerateLimit(FRAME_RATE_LIMIT);
    gameEntities = std::list<std::unique_ptr<IGameEntity>>();
}

void Game::pollEvents()
{
    while (window->pollEvent(currentEvent))
    {
        switch (currentEvent.type)
        {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (currentEvent.key.code == sf::Keyboard::Escape)
                    window->close();
                break;

            default:
                for (auto& entity : gameEntities)
                {
                    entity->handleEvent(currentEvent);
                }
                break;
        }            
    }
}

Game::Game()
{
    initVariables();
    initWindow();
}

Game::~Game()
{

}

void Game::update()
{
    pollEvents();
}

void Game::render()
{
    window->clear();
    
    for (auto& entity : gameEntities)
    {
        entity->draw(window);
    }

    window->display();
}

void Game::attachEntity(std::unique_ptr<IGameEntity>& entity)
{
    gameEntities.push_back(std::move(entity));
}

const bool Game::isRunning() const
{
	return window->isOpen();
}
