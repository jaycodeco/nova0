#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Texture* texture);
	~Player();

	void update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::RectangleShape* getCore() { return &body; }

	sf::Vector2f GetPosition() { return body.getPosition(); }
	void collided() { canJump = true; }

protected:
	sf::RectangleShape body;
	unsigned int row;
	float speed;
	bool faceRight, canJump;

};

