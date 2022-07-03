#pragma once
#include "IGameEntity.h"
#include <functional>

class Button : public IGameEntity
{
private:
	std::function<void()> onClick;
	sf::RectangleShape shape;
	sf::Vector2f lowerAnchorPoint;
	sf::Vector2f upperAnchorPoint;
	sf::Vector2f size;

	bool mouseInsideButton(const sf::Vector2f& mousePosition);
public:
	Button(std::function<void()> onClick, sf::Vector2f lowerAnchorPoint, float width, float height);
	void handleEvent(sf::Event& event);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

