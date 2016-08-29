#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <stack>
#include "World.hpp"
#include "Snake.hpp"
#include "Spawner.hpp"
#include "screens/Screen.hpp"

#define SNAKE_DEBUG

class Game
{
private:
	sf::RenderWindow window;
	bool paused;
	
	Screen *current;
	std::stack<Screen*> screens;
	Screen* Game::createFromScreenType(Screen::ScreenType type);
	
	sf::Font mainFont;
	sf::Color backgroundColor;

public:
	Game(const sf::Vector2f &screenSize);
	~Game();
	void run();
	void switchScreen(Screen::ScreenType newScreenType);

	const sf::Font &getFont() const { return mainFont; }
	const sf::Color &getBackgroundColor() const { return backgroundColor; }
	const sf::Vector2u &getWindowSize() const { return window.getSize(); }
	const sf::Vector2i &getMousePosition() const { return sf::Mouse::getPosition(window); }
	const sf::RenderWindow &getWindow() const { return window; }

	void end();
	void setPaused(bool paused_) { paused = paused_; }
};