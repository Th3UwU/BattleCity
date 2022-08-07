#include "input.hpp"
#include "gameCore.hpp"

void Input::update(void)
{
	// Get mouse position and convert coords relative to render (scale, view, offset)
	mousePos = sf::Mouse::getPosition(gameCore.window);
	mousePos.x -= gameCore.renderOffset.x; mousePos.x /= gameCore.scale;
	mousePos.y -= gameCore.renderOffset.y; mousePos.y /= gameCore.scale;

	sf::Vector2f viewPos = gameCore.renderView.getCenter();
	mousePos.x += viewPos.x - (gameCore.renderSize.x / 2);
	mousePos.y += viewPos.y - (gameCore.renderSize.y / 2);

	hold[INPUT::FULLSCREEN] = sf::Keyboard::isKeyPressed(sf::Keyboard::F11);
	hold[INPUT::UP] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	hold[INPUT::DOWN] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	hold[INPUT::LEFT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	hold[INPUT::RIGHT] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	hold[INPUT::ACTION] = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	for (unsigned int i = 0; i < inputCount; i++)
	{
		// Key pressed
		if ((!holdOld[i]) and (hold[i]))
			pressed[i] = true;
		else
			pressed[i] = false;

		// Key released
		if ((holdOld[i]) and (!hold[i]))
			released[i] = true;
		else
			released[i] = false;
		
		holdOld[i] = hold[i];
	}
}