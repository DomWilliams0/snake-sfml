#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "Screen.hpp"
#include "ButtonSelection.hpp"

class GameScreen;
class PauseScreen : public Screen
{
public:
	PauseScreen(Game *game);
	~PauseScreen();

	virtual void tick(float delta);
	virtual void render(sf::RenderWindow &window);
	virtual void handleInput(const sf::Event &event);

private:
	ButtonSelection<PauseScreen> buttons;
	void click(const std::string &button);
	void resume();

	sf::Sprite *snapshot;
	sf::Image image;
};

