#include <iostream>
#include <SFML\Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "PauseScreen.hpp"
#include "Screen.hpp"
#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../Logger.hpp"

PauseScreen::PauseScreen(Game *game_) : Screen(game_, Screen::PAUSE),
buttons(game_, this, sf::Vector2f(0, game->getWindowSize().y * -0.1f), &PauseScreen::click, std::vector < std::string > {"Resume", "Options", "Menu"})
{
	image = game->getWindow().capture();
	sf::Texture *texture = new sf::Texture;

	snapshot = new sf::Sprite;
	texture->loadFromImage(image);
	snapshot->setTexture(*texture);

	snapshot->setColor(sf::Color(200, 200, 200, 200));
}

PauseScreen::~PauseScreen()
{
	delete snapshot->getTexture();
	delete snapshot;
}

void PauseScreen::tick(float delta)
{
}

void PauseScreen::render(sf::RenderWindow &window)
{
	window.draw(*snapshot);
	buttons.render<PauseScreen>(window);
}

void PauseScreen::handleInput(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		resume();
	else
		buttons.handleInput<PauseScreen>(event);
}

void PauseScreen::click(const std::string &button)
{
	if (button == "menu")
		game->switchScreen(Screen::MENU); // todo: or gameover?
	else if (button == "options")
		game->switchScreen(Screen::OPTIONS);
	else if (button == "resume")
		resume();
}

void PauseScreen::resume()
{
	game->switchScreen(Screen::NONE);
}