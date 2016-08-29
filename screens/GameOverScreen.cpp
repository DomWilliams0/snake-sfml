#include <cassert>
#include "GameOverScreen.hpp"
#include "GameScreen.hpp"
#include "ButtonSelection.hpp"
#include "../Game.hpp"

GameOverScreen::GameOverScreen(Game *game_, Screen *oldScreen) : Screen(game_, Screen::GAMEOVER),
buttons(game_, this, sf::Vector2f(0, game->getWindowSize().y * 0.3), &GameOverScreen::click, std::vector < std::string > {"Retry", "Menu"})
{
	assert(oldScreen->type == Screen::GAME);
	GameScreen *gameScreen = static_cast<GameScreen*>(oldScreen);
	Snake snake = gameScreen->getSnake();

	yourScore.setText(game, "GAME OVER\n\nYour Score\n" + snake.getScoreString(), game->getWindowSize().y * 0.1);
}

void GameOverScreen::tick(float delta)
{
}

void GameOverScreen::render(sf::RenderWindow &window)
{
	window.clear(game->getBackgroundColor());
	yourScore.render(window);
	buttons.render<GameOverScreen>(window);
}

void GameOverScreen::handleInput(const sf::Event &event)
{
	buttons.handleInput<GameOverScreen>(event);
}

void GameOverScreen::click(const std::string &button)
{
	if (button == "retry")
		game->switchScreen(Screen::GAME);
	else if (button == "menu")
		game->switchScreen(Screen::MENU);

}