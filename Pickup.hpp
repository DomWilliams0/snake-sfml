#pragma once
#include <chrono>
#include "Entity.hpp"
#include "TimeTicker.hpp"
class Pickup :	public Entity
{
private:
	sf::CircleShape circle;
	int startSize;

	TimeTicker ticker;

public:
	Pickup(std::shared_ptr<World> w, float time);
	void render(sf::RenderWindow &window);
	void tick(float delta);
};

