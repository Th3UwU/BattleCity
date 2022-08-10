#ifndef GAME_CORE_HPP
#define GAME_CORE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>

#include "input.hpp"
#include "tank.hpp"
#include "block.hpp"

class GameCore
{
public:
    GameCore(void);
    ~GameCore(void);

    void loop(void);
    void update(void);
    void draw(void);
    void calcScale(void);

	sf::RenderWindow window;
	bool fullscreen;
	sf::String windowTitle;
	sf::Event event;

	sf::RenderTexture render;
    sf::Vector2u renderSize;
    sf::Vector2i renderOffset;
	int scale;
	sf::View renderView;
	sf::Sprite renderSprite;

	sf::Texture txrTank;
	sf::Texture txrBlock;
	sf::Texture txrMisc;

	//* TEST *//
	Tank tankTest;
	Block blockTest;
};

extern GameCore gameCore;

#endif