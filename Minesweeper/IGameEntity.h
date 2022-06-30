#pragma once
#include <SFML/Graphics.hpp>

class IGameEntity
{
public:
	virtual ~IGameEntity(){}
	virtual void HandleEvent(sf::Event& event) = 0;
	virtual void Draw(std::unique_ptr<sf::RenderWindow> &window) = 0;
};

