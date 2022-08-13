#include "tank.hpp"
#include "gameCore.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Bullet::Bullet(sf::Vector2f pos, char dir)
{
	collisionTank.left = pos.x;
	collisionTank.top = pos.y;

	switch (dir)
	{
		case 0: case 2:
			collisionTank.width = 3.0f;
			collisionTank.height = 4.0f;
			break;

		case 1: case 3:
			collisionTank.width = 4.0f;
			collisionTank.height = 3.0f;
			break;

		default: break;
	}

	//* Collision Block *//
	switch (dir)
	{
		case 0:
			collisionBlock.left = pos.x - 5.0f; collisionBlock.top = pos.y - 1.0f;
			collisionBlock.width = 13.0f; collisionBlock.height = 2.0f;
			break;

		case 2:
			collisionBlock.left = pos.x - 5.0f; collisionBlock.top = pos.y + 3.0f;
			collisionBlock.width = 13.0f; collisionBlock.height = 2.0f;
			break;

		case 1:
			collisionBlock.left = pos.x - 1.0f; collisionBlock.top = pos.y - 5.0f;
			collisionBlock.width = 2.0f; collisionBlock.height = 13.0f;
			break;

		case 3:
			collisionBlock.left = pos.x + 3.0f; collisionBlock.top = pos.y - 5.0f;
			collisionBlock.width = 2.0f; collisionBlock.height = 13.0f;
			break;
	}

	this->dir = dir;

	sprite.setTexture(gameCore.txrMisc);
	sprite.setTextureRect(sf::IntRect(0, 0, 3, 4));
	updateSprite();

	speed = 1.0f;
}

void Bullet::update(void)
{
	//* Movement *//
	switch (dir)
	{
		case 0: collisionTank.top -= speed; collisionBlock.top -= speed; break;
		case 2: collisionTank.top += speed; collisionBlock.top += speed; break;
		case 1: collisionTank.left -= speed; collisionBlock.left -= speed; break;
		case 3: collisionTank.left += speed; collisionBlock.left += speed; break;
	}

	//* Update sprite *//
	updateSprite();

	//* Block collision *//
	std::vector<bool*> bits;

	for (auto& i : gameCore.block)
		i.collision(collisionBlock, &bits);

	for (auto& i : bits)
		*i = false;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shapeCollisionTank;
	shapeCollisionTank.setPosition(sf::Vector2f(collisionTank.left, collisionTank.top));
	shapeCollisionTank.setSize(sf::Vector2f(collisionTank.width, collisionTank.height));
	shapeCollisionTank.setFillColor(sf::Color::Blue);

	sf::RectangleShape shapeCollisionBlock;
	shapeCollisionBlock.setPosition(sf::Vector2f(collisionBlock.left, collisionBlock.top));
	shapeCollisionBlock.setSize(sf::Vector2f(collisionBlock.width, collisionBlock.height));
	shapeCollisionBlock.setFillColor(sf::Color::Red);

	target.draw(shapeCollisionTank, states);
	//target.draw(sprite, states);
	target.draw(shapeCollisionBlock, states);
}

void Bullet::updateSprite(void)
{
	switch (dir)
	{
		case 0:
			sprite.setPosition(collisionTank.left, collisionTank.top);
			sprite.setRotation(0.0f);
			break;
		
		case 2:
			sprite.setPosition(collisionTank.left + 3.0f, collisionTank.top + 4.0f);
			sprite.setRotation(180.0f);
			break;
		
		case 1:
			sprite.setPosition(collisionTank.left, collisionTank.top + 3.0f);
			sprite.setRotation(270.0f);
			break;

		case 3:
			sprite.setPosition(collisionTank.left + 4.0f, collisionTank.top);
			sprite.setRotation(90.0f);
			break;
	}
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

	for (auto& i : gameCore.block)
	if (i.collision(testRect))
		return true;
	
	return false;
}
