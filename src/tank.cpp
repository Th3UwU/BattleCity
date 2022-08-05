#include "tank.hpp"
#include "gameCore.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Tank::Tank(sf::Vector2f pos, int rank)
{
	//* Rectangle *//
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = 16;
	rect.height = 16;

	//* Tank rank *//
	this->rank = rank;

	//* Sprite *//
	sprite.setTexture(gameCore.txrTank);
	sprite.setTextureRect(sf::IntRect(spriteFrame * 16, rank * 16, 16, 16));
	sprite.setOrigin(8.0f, 8.0f);

	spriteAnimationEnable = true;
	spriteAnimationSpeed = 5;
	spriteAnimation = 0;
	spriteFrame = 0;
}

void Tank::update(void)
{
	//* Animation *//
	spriteAnimationEnable =
	(input.hold[INPUT::UP]) || (input.hold[INPUT::DOWN]) ||
	(input.hold[INPUT::LEFT]) || (input.hold[INPUT::RIGHT]);
	
	if (spriteAnimationEnable)
	{
		if (spriteAnimation == 0)
		{
			spriteAnimation = spriteAnimationSpeed;
			spriteFrame = !spriteFrame;
			sprite.setTextureRect(sf::IntRect(spriteFrame * 16, rank * 16, 16, 16));
		}
		else
			spriteAnimation--;
	}

	//* Change sprite direction *//
	if (input.hold[INPUT::UP])
		sprite.setRotation(0.0f);
	else if (input.hold[INPUT::DOWN])
		sprite.setRotation(180.0f);
	else if (input.hold[INPUT::LEFT])
		sprite.setRotation(270.0f);
	else if (input.hold[INPUT::RIGHT])
		sprite.setRotation(90.0f);

	//* Sprite update *//
	sprite.setPosition(sf::Vector2f(rect.left + 8.0f, rect.top + 8.0f));
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape test;
	test.setPosition(sf::Vector2f(rect.left, rect.top));
	test.setSize(sf::Vector2f(rect.width, rect.height));
	test.setFillColor(sf::Color::Red);

	target.draw(test, states);
	target.draw(sprite, states);
}