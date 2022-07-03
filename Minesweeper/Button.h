#pragma once
#include "IGameEntity.h"
#include <functional>

/// <summary>
///     Creates a button that triggers the <c> onClick </c> function, which is passed on the constructor. 
/// </summary>
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
	Button(const std::function<void()>& onClick, const sf::Vector2f& lowerAnchorPoint, float width, float height);

	void handleEvent(sf::Event& event);

	void draw(std::unique_ptr<sf::RenderWindow>& window);
};

