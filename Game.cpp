#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stack>
#include "Game.hpp"
#include "World.hpp"
#include "Snake.hpp"
#include "Spawner.hpp"
#include "Logger.hpp"
#include "screens/Screen.hpp"
#include "screens/GameScreen.hpp"
#include "screens/MenuScreen.hpp"
#include "screens/PauseScreen.hpp"
#include "screens/GameOverScreen.hpp"

using sf::Vector2f;
using sf::Color;
using sf::RenderWindow;

Game::Game(const Vector2f &screenSize) :
window(sf::VideoMode(screenSize.x, screenSize.y), "Snake", sf::Style::Default, sf::ContextSettings(0, 0, 4)), paused(false), backgroundColor(sf::Color(20, 20, 22))
{
	// set frame rate
	window.setFramerateLimit(600);

	// create logger
	Logger::createLogger(std::cout, Logger::Level::DEBUG);

	// load fonts
	if (mainFont.loadFromFile("res/font.ttf"))
		Logger::logInfo("Font loaded successfully");

	// load menu
	switchScreen(Screen::MENU);
}

Game::~Game()
{
	// destruct all screenss
	/*for (int i = 0; i < screens.size(); i++)
		switchScreen(Screen::NONE);*/
}

void Game::run()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
				current->handleInput(event);
		}


		float delta(clock.restart().asSeconds());

		if (!paused)
			current->tick(delta);

		window.clear();
		current->render(window);

		// todo: temporary
		//sf::Vertex halfLine[] = { sf::Vertex(sf::Vector2f(getWindowSize().x / 2, 0)), sf::Vertex(sf::Vector2f(getWindowSize().x / 2, getWindowSize().y)) };
		//window.draw(halfLine, 2, sf::Lines);
		// todo: temporary

		window.display();
	}
}

void Game::switchScreen(Screen::ScreenType newScreenType)
{
	// destruct current
	if (newScreenType == Screen::ScreenType::NONE)
	{
		delete current;
		screens.pop();
		current = screens.top();
	}

	// push new screen onto stack
	else
	{
		Screen *newScreen(createFromScreenType(newScreenType));
		if (!newScreen) return;

		bool shouldDestruct = (current && current->type != Screen::GAME && newScreenType != Screen::PAUSE);

		if (shouldDestruct)
		{
			screens.pop();
			delete current;
		}

		current = newScreen;
		screens.push(newScreen);
	}

	window.setMouseCursorVisible(current->showMouse);
}

Screen* Game::createFromScreenType(Screen::ScreenType type)
{
	switch (type)
	{
	case Screen::GAME: return new GameScreen(this);
		break;
	case Screen::MENU: return new MenuScreen(this);
		break;
	case Screen::PAUSE: return new PauseScreen(this);
		break;
	case Screen::OPTIONS: Logger::logInfo("No options for now!");
		return NULL;
		break;
	case Screen::GAMEOVER: return new GameOverScreen(this, current);
		break;
	}
}

void Game::end()
{
	window.close();
	Logger::logDebug("Game ended through game.end()");
}


int main()
{
	std::srand(time(NULL));

	// todo random rule changes, like avoid yellows, get reds, you can now go through walls etc
	Game game(Vector2f(640, 640));
	game.run();
}
