#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Pickup.hpp"
#include "TimeTicker.hpp"

class Spawner
{
private:
	std::vector<Pickup> pickups;
	std::shared_ptr<World> world;
	TimeTicker ticker;

	void spawnPickup();

public:
	Spawner() {}
	Spawner(std::shared_ptr<World> w) : world(w) {};
	void render(sf::RenderWindow &window);
	void tick(float delta);
};

