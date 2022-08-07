#include "block.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Block::Block(sf::Vector2f pos, int type)
{
	//* Rectangle *//
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = 16;
	rect.height = 16;

	//* Block type *//
	this->type = type;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape collisionBox;
	collisionBox.setPosition(sf::Vector2f(rect.left, rect.top));
	collisionBox.setSize(sf::Vector2f(rect.width, rect.height));
	collisionBox.setFillColor(sf::Color::Red);

	target.draw(collisionBox, states);
}