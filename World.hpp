#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include "Pickup.hpp"
#include "TimeTicker.hpp"
#include "Snake.hpp"
#define printColor(color) std::cout << static_cast<int>(color.r) << " " << static_cast<int>(color.g) << " " << static_cast<int>(color.b) << std::endl;

class World
{
private:
	struct Cell
	{
		Snake *snake;
		TimeTicker ticker;
		bool blocked;
		bool hasSnake;

		Cell() : snake(NULL), blocked(false), hasSnake(false) {}

		void tick(float delta)
		{
			if (hasSnake && !ticker.tick(delta))
				hasSnake = false;
		}

		sf::Color getColor(const sf::Color &defaultColor)
		{
			return hasSnake && snake ? snake->color : defaultColor;
		}
	};

public:
	World(const sf::Vector2f &size, int cellDimension);

	bool canTouch(int x, int y) { Cell *c(get(x, y)); return c->blocked || !c->hasSnake; }
	bool isInRange(int x, int y) const { return x >= 0 && x < dimensions.x && y >= 0 && y < dimensions.y; }
	const sf::Vector2f& size() const { return dimensions; }

	void tick(float delta);
	void render(sf::RenderWindow &window);
	void register_movement(Snake *snake, int x, int y, float delta);
	void lengthenSnake(Snake *snake);
	void wrapAround(float &x, float &y);

	Snake *getSnake(const sf::Vector2f &vec);

	const int cellSize;

private:
	std::vector<Cell> grid;
	sf::Vector2f dimensions;
	Cell *get(int x, int y) { return &grid.at((x*dimensions.x) + y); }
};
