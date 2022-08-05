#ifndef TANK_HPP
#define TANK_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Tank : public sf::Drawable
{
public:
	Tank(void) = delete;
	Tank(sf::Vector2f pos, int rank);

	~Tank(void) = default;

	void update(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::FloatRect rect;
	int rank;

	sf::Sprite sprite;
	bool spriteAnimationEnable;
	int spriteAnimationSpeed;
	int spriteAnimation;
	int spriteFrame;
};

#endif