#include <iostream>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "World.hpp"
#include "Game.hpp"

using sf::Vector2f;
using sf::Color;
using sf::RenderWindow;

Snake::Snake() : Entity(world, snakeColor), length(45), speed(0.1), ticker(speed), score(0)
{
	static unsigned int lastId = 0;
	id = lastId++;
}


void Snake::spawn(std::shared_ptr<World> world)
{
	this->world = world;
	Vector2f worldSize(world->size());
	move(worldSize.x / 2, worldSize.y / 2);
	velocity.y = 1;
}

void Snake::render(RenderWindow &window)
{
	// body is rendered in world
}

void Snake::tick(float delta)
{
	if (!ticker.tick(delta))
	{

		if (validVelocity(nextVelocity) && !((nextVelocity.x > 0 && velocity.x < 0) || (nextVelocity.x < 0 && velocity.x > 0) ||
			(nextVelocity.y > 0 && velocity.y < 0) || (nextVelocity.y < 0 && velocity.y > 0)))
			velocity = nextVelocity;

		assert(validVelocity(velocity)); // must be moving

		float x = cellPos.x + velocity.x;
		float y = cellPos.y + velocity.y;
		move(x, y, delta);
	}

}

void Snake::processKeypress(int key)
{
	Vector2f v;

#ifdef SNAKE_DEBUG
	switch (key)
	{
	case sf::Keyboard::Space:
		*this += 5;
		increaseLength(); break;
	case sf::Keyboard::Q:
		dead = true; break;
	}
#endif

	if (key == sf::Keyboard::W) v.y = -1;
	else if (key == sf::Keyboard::S) v.y = 1;
	else if (key == sf::Keyboard::A) v.x = -1;
	else if (key == sf::Keyboard::D) v.x = 1;
	else return;

	nextVelocity = v;
}

void Snake::move(float cellX, float cellY, float delta)
{
	world->wrapAround(cellX, cellY);
	cellPos.x = cellX;
	cellPos.y = cellY;
	world->register_movement(this, cellX, cellY, delta);
}

void Snake::increaseLength()
{
	length++;
	world->lengthenSnake(this);
}
