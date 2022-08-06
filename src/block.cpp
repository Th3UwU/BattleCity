#include "block.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Block::Block(sf::Vector2f pos, int type)
: Entity(pos)
{
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