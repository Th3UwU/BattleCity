#include "block.hpp"
#include "gameCore.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <cstring>

Block::Block(sf::Vector2f pos, int type)
{
	//* Position *//
	this->pos = pos;

	//* Block type *//
	this->type = type;

	//* bits (small blocks) *//
	std::memset(bit, true, sizeof(bool) * 16);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape collisionBox;
	collisionBox.setSize(sf::Vector2f(4.0f, 4.0f));
	collisionBox.setFillColor(sf::Color::Red);

	sf::Sprite sprite;
	sprite.setTexture(gameCore.txrBlock);

	for (int i = 0; i < 16; i++)
	if (bit[i])
	{
		sf::Vector2f testPos
		(
			(4.0f * int(i % 4)) + pos.x,
			(4.0f * int(i / 4)) + pos.y
		);

		collisionBox.setPosition(testPos);

		sprite.setPosition(testPos.x, testPos.y);
		sprite.setTextureRect(sf::IntRect(4 * (i % 4), 4 * (i / 4), 4, 4));

		target.draw(collisionBox, states);
		target.draw(sprite, states);
	}
}

bool Block::collision(sf::FloatRect& rect)
{

	sf::FloatRect rectBit;
	rectBit.width = 4;
	rectBit.height = 4;

	for (int i = 0; i < 16; i++)
	if (bit[i])
	{
		rectBit.left = (4.0f * int(i % 4)) + pos.x;
		rectBit.top = (4.0f * int(i / 4)) + pos.y;

		if (rectBit.intersects(rect))
			return true;
	}

	return false;
}

bool Block::collision(sf::FloatRect& rect, std::vector<bool*>& collisionBit)
{
	bool collision = false;

	sf::FloatRect rectBit;
	rectBit.width = 4;
	rectBit.height = 4;

	for (int i = 0; i < 16; i++)
	if (bit[i])
	{
		rectBit.left = (4.0f * int(i % 4)) + pos.x;
		rectBit.top = (4.0f * int(i / 4)) + pos.y;

		if (rectBit.intersects(rect))
		{
			collision = true;
			collisionBit.push_back(&bit[i]);
		}
	}

	return collision;
}