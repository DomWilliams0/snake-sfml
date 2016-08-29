#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "TimeTicker.hpp"


const static sf::Color snakeColor(sf::Color(220, 130, 20));
class Snake : public Entity
{
public:
	Snake();
	void spawn(std::shared_ptr<World> w);
	virtual void render(sf::RenderWindow &window);
	virtual void tick(float delta);

	void init(std::shared_ptr<World> world);
	void processKeypress(int key);
	void move(float cellX, float cellY, float delta = 0.0);
	void increaseLength();

	inline int getScore() const { return score; }
	Snake &operator+=(int scoreAddition)
	{
		score += scoreAddition;
		return *this;
	}

	inline std::string getScoreString()
	{
		return (score < 10 ? "0" : "") + std::to_string(score);
	}


	unsigned int id;
	int length;
	float speed;

private:
	TimeTicker ticker;
	sf::Vector2f nextVelocity;
	unsigned int score;

	inline bool validVelocity(const sf::Vector2f &vec) { return vec.x != 0 || vec.y != 0; }
};


