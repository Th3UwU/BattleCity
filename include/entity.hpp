#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Drawable
{
public:
	Entity(void) = delete;
	Entity(sf::Vector2f pos);

	virtual ~Entity(void) = default;

	sf::FloatRect rect;
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif