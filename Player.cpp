#include "Player.h"


Player::Player(sf::Texture* texture)
{
	this->speed = 70.5f;
	canJump = 1;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(32.0f, 32.0f));
	body.setPosition(40.0f, 40.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	sf::Vector2f displacement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		displacement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		displacement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump)
	{
		canJump = false;
		displacement.y -= 700.0f * deltaTime;
	}


	displacement.y += 70.5f * deltaTime;

	if (displacement.x == 0)
	{
		row = 0;
	}
	else
	{
		row = 1;
		faceRight = (displacement.x > 0) ? true : false;
		
	}


	body.move(displacement);
	//canJump = false;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

