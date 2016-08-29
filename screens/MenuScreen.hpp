#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "ButtonSelection.hpp"
#include "Screen.hpp"
#include "../World.hpp"
#include "../Snake.hpp"

class Game;
class MenuScreen : public Screen
{
public:
	MenuScreen(Game *game);
	virtual void tick(float delta);
	virtual void render(sf::RenderWindow &window);
	virtual void handleInput(const sf::Event &event);


private:
	sf::Text title;

	ButtonSelection<MenuScreen> buttons;
	void click(const std::string &button);
};

