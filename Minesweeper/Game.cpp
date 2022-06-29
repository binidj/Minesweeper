#include "Game.h"

void Game::initVariables()
{
    window = nullptr;
    videoMode = sf::VideoMode(512, 512);
}

void Game::initWindow()
{
    window = std::make_unique<sf::RenderWindow>(videoMode, "SFML works!");
}

void Game::pollEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;

            default:
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
    
    // draw objects

    window->display();
}



const bool Game::isRunning() const
{
	return window->isOpen();
}
