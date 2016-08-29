#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

namespace Util
{
	inline static void centre(sf::Text &text, Game *game, int y = -1)
	{
		text.setPosition(game->getWindowSize().x / 2 - text.getLocalBounds().width / 2, y < 0 ? text.getPosition().y : y);
	}

	static sf::Color darken(const sf::Color &color, int delta)
	{
		auto r = color.r < delta ? 0 : color.r - delta;
		auto g = color.g < delta ? 0 : color.g - delta;
		auto b = color.b < delta ? 0 : color.b - delta;
		return sf::Color(r, g, b);
	}

}
