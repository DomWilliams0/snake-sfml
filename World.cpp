#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Snake.hpp"
#include "World.hpp"

using sf::Vector2f;

World::World(const Vector2f &size, int cellDimension) : dimensions(size), cellSize(cellDimension)
{
	for (unsigned int i = 0; i < size.x * size.y; ++i)
		grid.push_back(Cell());
}

void World::tick(float delta)
{
	for (Cell &cell : grid)
		cell.tick(delta);
}

void World::render(sf::RenderWindow &window)
{
	const static sf::Color solidColor(sf::Color(30, 30, 40));
	const static sf::Color gridColor(sf::Color(50, 50, 60));
	sf::RectangleShape tail(Vector2f(cellSize, cellSize));
	sf::RectangleShape grid(tail);

	grid.setFillColor(sf::Color::Transparent);
	grid.setOutlineColor(gridColor);
	grid.setOutlineThickness(1);

	for (int x = 0; x < dimensions.x; x++)
	{
		for (int y = 0; y < dimensions.y; y++)
		{
			Cell *c(get(x, y));

			// draw snakes
			tail.setPosition(x*cellSize, y*cellSize);
			tail.setFillColor(c->getColor(solidColor));
			window.draw(tail);

			// draw grid
			grid.setPosition(tail.getPosition());
			window.draw(grid);
		}
	}
}

void World::register_movement(Snake *snake, int x, int y, float delta)
{
	if (!isInRange(x, y))
		snake->dead = true;
	else
	{
		Cell *c = get(x, y);
		if (c->hasSnake)
			snake->dead = true;
		else
		{
			c->snake = snake;
			c->hasSnake = true;
			c->ticker.reset((snake->length + delta) * (snake->speed + delta));
		}

	}
}

void World::lengthenSnake(Snake *snake)
{
	for (Cell &cell : grid)
		if (cell.snake == snake)
			cell.ticker.duration += snake->speed;
}


Snake *World::getSnake(const Vector2f &vec)
{
	Cell *c = get(vec.x, vec.y);
	if (c->hasSnake) return c->snake;
	return NULL;
}

void World::wrapAround(float &x, float &y)
{
	if (x < 0) x = dimensions.x - 1;
	else if (x >= dimensions.x) x = 0;

	if (y < 0) y = dimensions.y - 1;
	else if (y >= dimensions.y) y = 0;

}