#include "tank.hpp"
#include "gameCore.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Bullet::Bullet(sf::Vector2f pos, char dir)
{
	rect.left = pos.x;
	rect.top = pos.y;

	switch (dir)
	{
		case 0: case 2:
			rect.width = 3.0f;
			rect.height = 4.0f;
			break;

		case 1: case 3:
			rect.width = 4.0f;
			rect.height = 3.0f;
			break;

		default: break;
	}

	this->dir = dir;
}

void Bullet::update(void)
{
	switch (dir)
	{
		case 0: rect.top -= 1.0; break;
		case 2: rect.top += 1.0; break;
		case 1: rect.left -= 1.0; break;
		case 3: rect.left += 1.0; break;
	}
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape collisionBox;
	collisionBox.setPosition(sf::Vector2f(rect.left, rect.top));
	collisionBox.setSize(sf::Vector2f(rect.width, rect.height));
	collisionBox.setFillColor(sf::Color::Blue);

	target.draw(collisionBox, states);
}

Tank::Tank(sf::Vector2f pos, int rank)
{
	//* Rectangle *//
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = 16.0f;
	rect.height = 16.0f;

	//* Tank rank *//
	this->rank = rank;
	
	//* Face direction *//
	dir = 0;

	//* Sprite *//
	sprite.setTexture(gameCore.txrTank);
	sprite.setTextureRect(sf::IntRect((spriteFrame * 16) + (dir * 32), rank * 16, 16, 16));
	sprite.setOrigin(8.0f, 8.0f);

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
		}
		else
			spriteAnimation--;
	}

	//* Movement *//
	if (input.hold[INPUT::UP])
	{
		if (!collision(0, -1))
			rect.top += -1;
		dir = 0;
	}
	else if (input.hold[INPUT::DOWN])
	{
		if (!collision(0, 1))
			rect.top += 1;
		dir = 2;
	}
	else if (input.hold[INPUT::LEFT])
	{
		if (!collision(-1, 0))
			rect.left += -1;
		dir = 1;
	}
	else if (input.hold[INPUT::RIGHT])
	{
		if (!collision(1, 0))
			rect.left += 1;
		dir = 3;
	}

	//* Sprite update *//
	sprite.setTextureRect(sf::IntRect((spriteFrame * 16) + (dir * 32), rank * 16, 16, 16));
	sprite.setPosition(sf::Vector2f(rect.left + 8.0f, rect.top + 8.0f));

	//* Update bullet *//
	for (auto i = bullet.begin(); i != bullet.end(); i++)
		i->update();

	if (input.pressed[INPUT::ACTION])
	{
		float x, y;
		switch (dir)
		{
			case 0: x = rect.left + 6.0f; y = rect.top - 2.0f; break;
			case 2: x = rect.left + 6.0f; y = rect.top + 14.0f; break;
			case 1: x = rect.left - 2.0f; y = rect.top + 6.0f; break;
			case 3: x = rect.left + 14.0f; y = rect.top + 6.0f; break;
		}
		printf("dir: %i\n", dir);
		bullet.push_back(Bullet(sf::Vector2f(x, y), dir));
	}
}

void Tank::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape collisionBox;
	collisionBox.setPosition(sf::Vector2f(rect.left, rect.top));
	collisionBox.setSize(sf::Vector2f(rect.width, rect.height));
	collisionBox.setFillColor(sf::Color::Black);

	target.draw(collisionBox, states);
	target.draw(sprite, states);

	for (auto i = bullet.begin(); i != bullet.end(); i++)
		target.draw(*i);
}

bool Tank::collision(int x, int y)
{
	sf::FloatRect testRect = rect;
	testRect.left += x;
	testRect.top += y;

	return gameCore.blockTest.rect.intersects(testRect);
}
