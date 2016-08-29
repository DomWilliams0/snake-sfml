#include <chrono>
#include "Pickup.hpp"
#include "Snake.hpp"
#include "World.hpp"

Pickup::Pickup(std::shared_ptr<World> w, float time) : Entity(w, sf::Color::Yellow), ticker(time), startSize(w->cellSize/2)
{
	for (int i = 0; i < 50; i++) // timeout
	{
		cellPos = sf::Vector2f(rand() % static_cast<int>(world->size().x), rand() % static_cast<int>(world->size().y));
		if (!world->getSnake(cellPos))
			break;
	}

	circle.setRadius(startSize);
	circle.setOrigin(-startSize, -startSize);
	circle.setPosition(cellPos.x * world->cellSize, cellPos.y * world->cellSize);

	circle.setFillColor(color);
}

void Pickup::render(sf::RenderWindow &window)
{
	window.draw(circle);
}

void Pickup::tick(float delta)
{
	// expired
	if (!ticker.tick(delta))
	{
		dead = true;
		return;
	}

	// snake hit
	Snake *snake = world->getSnake(cellPos);
	if (snake)
	{
		*snake += 1;
		snake->increaseLength();
		dead = true;
		return;
	}

	// shrink
	float progress = 1 - (static_cast<float>(ticker.lifeTime) / ticker.duration);
	float newSize = progress * startSize;
	circle.setPosition(cellPos.x * world->cellSize - newSize, cellPos.y * world->cellSize - newSize);
	circle.setRadius(newSize);
}
