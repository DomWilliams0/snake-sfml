#include <iostream>
#include <algorithm>
#include "Spawner.hpp"
#include "Pickup.hpp"

void Spawner::render(sf::RenderWindow &window)
{
	for (auto &p : pickups)
		p.render(window);
}

void Spawner::tick(float delta)
{
	auto end = std::remove_if(pickups.begin(), pickups.end(), [](const Pickup &p) {return p.dead; });
	pickups.erase(end, pickups.end());
	if (pickups.empty() || !ticker.tick(delta))
	{
		spawnPickup();
		ticker.reset(((rand() % 20) + 20) / 10.0f);
	}

	for (auto &p : pickups)
		p.tick(delta);

}

void Spawner::spawnPickup()
{
	pickups.push_back(Pickup(world, (rand() % 3) + 4));
}