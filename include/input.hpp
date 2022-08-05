#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/System.hpp>

enum INPUT : unsigned int
{
	NONE = 0,
	FULLSCREEN,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Input
{
public:
	static inline const unsigned int inputCount = 6;

	Input(void) = default;
	void update(void);

	sf::Vector2i mousePos;

	bool holdOld[inputCount];
	
	bool hold[inputCount];
	bool pressed[inputCount];
	bool released[inputCount];
};

extern Input input;

#endif
