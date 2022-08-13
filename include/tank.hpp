#ifndef TANK_HPP
#define TANK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class Bullet : public sf::Drawable
{
public:
	Bullet(void) = delete;
	Bullet(sf::Vector2f pos, char dir);

	~Bullet(void) = default;

	void update(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void updateSprite(void);

	sf::FloatRect collisionTank;
	sf::FloatRect collisionBlock;
	int dir;
	
	sf::Sprite sprite;
	float speed;
};


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
	int dir;
	sf::Sprite sprite;

	int rank;

	bool spriteAnimationEnable;
	int spriteAnimationSpeed;
	int spriteAnimation;
	int spriteFrame;

	std::vector<Bullet> bullet;
};

#endif