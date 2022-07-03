#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "IGameEntity.h"
#include "Constants.h"

/// <summary>
///     Wraps main SFML rendering functionality and all <c> IGameEntity </c> attached.
/// </summary>
class Game
{
private:
	std::unique_ptr<sf::RenderWindow> window;

	sf::VideoMode videoMode;

	sf::Event currentEvent;

	/// <summary>
	///     A list of all game entities in the game.
	/// </summary>
	std::list<std::unique_ptr<IGameEntity>> gameEntities;

public:
	Game();

	virtual ~Game();

	void initVariables();

	void initWindow();

	/// <summary>
	///     SFML event polling.
	/// </summary>
	void pollEvents();

	void update();

	void render();

	/// <summary>
	///     Attaches an <c> IGameEntity </c> to the game entity list.
	/// </summary>
	void attachEntity(std::unique_ptr<IGameEntity>& entity);

	const bool isRunning() const;
};

