#include <iostream>
#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "MenuScreen.hpp"
#include "../Game.hpp"
#include "../Util.hpp"


MenuScreen::MenuScreen(Game *game_) : Screen(game_, Screen::MENU), 
buttons(game_, this, sf::Vector2f(), &MenuScreen::click, std::vector<std::string>{ "Play", "Options", "Quit" })
{
	// title
	title.setFont(game->getFont());
	title.setString("Snake");
	title.setCharacterSize(100);
	title.setColor(sf::Color::White);
	title.setStyle(sf::Text::Italic);

	Util::centre(title, game, game->getWindowSize().y * 0.1);
}

void MenuScreen::render(sf::RenderWindow &window)
{
	window.clear(game->getBackgroundColor());
	window.draw(title);

	buttons.render<MenuScreen>(window);
}

void MenuScreen::tick(float delta)
{
}

void MenuScreen::click(const std::string &button)
{
	if (button == "quit")
		game->end();
	else if (button == "play")
		game->switchScreen(Screen::GAME);
	else if (button == "options")
		game->switchScreen(Screen::OPTIONS);
}

void MenuScreen::handleInput(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		game->end();
	else
		buttons.handleInput<MenuScreen>(event);
}

