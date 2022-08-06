#include "entity.hpp"

Entity::Entity(sf::Vector2f pos)
{
	//* Rectangle *//
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = 16;
	rect.height = 16;
}