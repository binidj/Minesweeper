#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "IGameEntity.h"
#include "Constants.h"

class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;
	sf::VideoMode videoMode;
	sf::Event currentEvent;
	std::list<std::unique_ptr<IGameEntity>> gameEntities;

public:
	Game();
	virtual ~Game();
	void initVariables();
	void initWindow();
	void pollEvents();
	void update();
	void render();
	void attachEntity(std::unique_ptr<IGameEntity>& entity);
	const bool isRunning() const;
};

