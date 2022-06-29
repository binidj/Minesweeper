#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;
	sf::VideoMode videoMode;
	sf::Event event;
	// grid


public:
	Game();
	virtual ~Game();
	void initVariables();
	void initWindow();
	void pollEvents();
	void update();
	void render();
	const bool isRunning() const;
};

