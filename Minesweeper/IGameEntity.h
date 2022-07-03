#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
///		An interface that molds an in game object entity. 
/// </summary>
class IGameEntity
{
public:
	virtual ~IGameEntity(){}

	virtual void handleEvent(sf::Event& event) = 0;

	virtual void draw(std::unique_ptr<sf::RenderWindow> &window) = 0;
};

