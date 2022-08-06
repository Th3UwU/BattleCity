#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "entity.hpp"

class Block : public Entity
{
public:
	Block(void) = delete;
	Block(sf::Vector2f pos, int type);

	~Block(void) = default;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int type;
};

#endif