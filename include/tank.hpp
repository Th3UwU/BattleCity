#ifndef TANK_HPP
#define TANK_HPP

#include "entity.hpp"

class Tank : public Entity
{
public:
	Tank(void) = delete;
	Tank(sf::Vector2f pos, int rank);

	~Tank(void) = default;

	void update(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool collision(int x, int y);

	int rank;

	bool spriteAnimationEnable;
	int spriteAnimationSpeed;
	int spriteAnimation;
	int spriteFrame;
};

#endif