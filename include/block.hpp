#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class Block : public sf::Drawable
{
public:
	Block(void) = delete;
	Block(sf::Vector2f pos, int type);

	~Block(void) = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool collision(sf::FloatRect& rect);
	bool collision(sf::FloatRect& rect, std::vector<bool*>& collisionBit);

	sf::Vector2f pos;

	int type;
	bool bit[16];
};

#endif