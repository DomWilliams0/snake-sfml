#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class World;

class Entity
{
protected:
	std::shared_ptr<World> world;
	sf::Vector2f cellPos;
	sf::Vector2f velocity;

public:
	Entity() {}
	Entity(std::shared_ptr<World> w, const sf::Color &colour) : world(w), color(colour), dead(false) { };
	virtual void render(sf::RenderWindow &window) = 0;
	virtual void tick(float delta) = 0;

	bool isMoving() const { return velocity.x != 0 || velocity.y != 0; }
	
	sf::Color color;
	bool dead;
};
