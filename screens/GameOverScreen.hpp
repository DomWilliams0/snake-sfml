#pragma once
#include "Screen.hpp"
#include "ButtonSelection.hpp"
#include "TextBlock.hpp"

class GameOverScreen : public Screen
{

public:
	GameOverScreen(Game *game_, Screen *oldScreen);
	virtual void tick(float delta);
	virtual void render(sf::RenderWindow &window);
	virtual void handleInput(const sf::Event &event);

private:
	ButtonSelection<GameOverScreen> buttons;
	sf::Text score;
	TextBlock yourScore;
	void click(const std::string &button);
	


};