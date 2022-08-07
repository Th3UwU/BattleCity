#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Block : public sf::Drawable
{
public:
	Block(void) = delete;
	Block(sf::Vector2f pos, int type);

	~Block(void) = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect rect;
	sf::Sprite sprite;

	int type;
};

#endif