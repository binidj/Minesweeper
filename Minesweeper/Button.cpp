#include "Button.h"

bool Button::mouseInsideButton(const sf::Vector2f &mousePosition)
{
	return (mousePosition.x >= lowerAnchorPoint.x && mousePosition.y >= lowerAnchorPoint.y &&
			mousePosition.x <= upperAnchorPoint.x && mousePosition.y <= upperAnchorPoint.y);
}

Button::Button(std::function<void()> onClick, sf::Vector2f lowerAnchorPoint, float width, float height) : 
	onClick(onClick), lowerAnchorPoint(lowerAnchorPoint)
{
	size = sf::Vector2f(width, height);
	upperAnchorPoint = sf::Vector2f(lowerAnchorPoint.x + size.x, lowerAnchorPoint.y + size.y);

	shape.setSize(size);
	shape.setOutlineColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOutlineThickness(2.f);
	shape.setPosition(lowerAnchorPoint);
}

void Button::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::EventType::MouseButtonPressed)
	{
		const sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
		
		if (event.mouseButton.button == sf::Mouse::Button::Left && mouseInsideButton(mousePosition))
		{
			onClick();
		}
	}
	
}

void Button::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(shape);
}
