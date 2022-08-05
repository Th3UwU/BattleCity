#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/System.hpp>

class Input
{
private:
	static const unsigned int inputCount = 2;

public:
	Input(void) = default;
	void update(void);

	sf::Vector2i mousePos;
	
	enum INPUT : unsigned int
	{
		NONE = 0,
		FULLSCREEN
	};

	bool holdOld[inputCount];
	
	bool hold[inputCount];
	bool pressed[inputCount];
	bool released[inputCount];
};

extern Input input;

#endif
