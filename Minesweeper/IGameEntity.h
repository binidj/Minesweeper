#pragma once
#include <SFML/Graphics.hpp>

class IGameEntity
{
public:
	virtual ~IGameEntity(){}
	virtual void handleEvent(sf::Event& event) = 0;
	virtual void draw(std::unique_ptr<sf::RenderWindow> &window) = 0;
};

