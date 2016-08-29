#pragma once
#include <SFML/Window.hpp>
#include <memory>
#include "Screen.hpp"
#include "../World.hpp"
#include "../Spawner.hpp"
#include "../Snake.hpp"

class Game;
class GamePrepScreen;
class GameScreen :	public Screen
{
public:
	GameScreen(Game *game);
	virtual void tick(float delta);
	virtual void render(sf::RenderWindow &window);
	virtual void handleInput(const sf::Event &event);

	inline Snake &getSnake() { return snake; }

private:
	Snake snake;
	std::shared_ptr<World> world;
	Spawner spawner;

	unsigned int snakeScore;
	sf::Text scoreText;
};

