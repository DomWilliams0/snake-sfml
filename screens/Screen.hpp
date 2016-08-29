#pragma once
#include <SFML/Graphics.hpp>

class Game;

class Screen
{
public:
	enum ScreenType
	{
		NONE, MENU, OPTIONS, GAME, PAUSE, GAMEOVER
	};

	Screen(Game *game_, ScreenType screenType, bool mouse = true) : game(game_), type(screenType), showMouse(mouse) {}
	virtual void tick(float delta) = 0;
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void handleInput(const sf::Event &event) = 0;

	const ScreenType type;
	bool showMouse;

protected:
	Game *game;
	sf::Font mainFont;
};