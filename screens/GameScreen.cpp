#include <iostream>
#include <memory>
#include <SFML\Graphics.hpp>
#include "../Logger.hpp"
#include "../World.hpp"
#include "../Spawner.hpp"
#include "../Snake.hpp"
#include "GameScreen.hpp"
#include "../Game.hpp"

GameScreen::GameScreen(Game *game) : Screen(game, Screen::GAME, false), snakeScore(99)
{
	World w(sf::Vector2f(40, 40), 16); // todo: calculate world dimensions from screen size
	auto shared = std::make_shared<World>(w);
	world = shared;
	spawner = Spawner(shared);
	snake.spawn(shared);

	scoreText.setFont(game->getFont());
	scoreText.setCharacterSize(w.cellSize * 2);
	const auto textSize = scoreText.getLocalBounds();
	scoreText.setPosition(textSize.width / 2, textSize.height / 2);
	scoreText.setColor(sf::Color::Red);
}

void GameScreen::tick(float delta)
{
	if (snake.dead)
	{
		game->switchScreen(Screen::GAMEOVER);
		Logger::logDebug("Snake death");
	}
	else
	{
		snake.tick(delta);
		world->tick(delta);
		spawner.tick(delta);

		if (snake.getScore() != snakeScore)
			scoreText.setString(snake.getScoreString());
	}
}

void GameScreen::render(sf::RenderWindow &window)
{
	snake.render(window);
	world->render(window);
	spawner.render(window);

	window.draw(scoreText);
}

void GameScreen::handleInput(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto key = event.key.code;
		if (key == sf::Keyboard::Escape)
			game->switchScreen(PAUSE);

		else // todo: check that key is a valid key for the snake ie. arrows or wasd
			snake.processKeypress(event.key.code);
	}
}
