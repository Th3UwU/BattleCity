#ifndef TANK_HPP
#define TANK_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Tank : public sf::Drawable
{
public:
	Tank(void) = delete;
	Tank(sf::Vector2f pos, int rank);

	~Tank(void) = default;

	void update(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool collision(int x, int y);

	sf::FloatRect rect;
	sf::Sprite sprite;

	int rank;

	bool spriteAnimationEnable;
	int spriteAnimationSpeed;
	int spriteAnimation;
	int spriteFrame;
};

#endif