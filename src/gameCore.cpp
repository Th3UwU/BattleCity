#include "gameCore.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

GameCore::GameCore(void)
{
	fullscreen = false;
	windowTitle = sf::String("Memory Game");
	window.create(sf::VideoMode(800, 600), windowTitle);
    
    renderSize.x = 256;
    renderSize.y = 240;

    render.create(renderSize.x, renderSize.y);
    renderView = render.getDefaultView();
	renderView.move(70, 0);
    render.setView(renderView);
    renderSprite.setTexture(render.getTexture());
    calcScale();
}

GameCore::~GameCore(void)
{

}

void GameCore::loop(void)
{
	while (window.isOpen())
	{	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				calcScale();
			}
		}

		//* Update *//
		update();

		//* Draw *//
		render.setView(renderView);
		render.clear(sf::Color(0, 100, 100, 255));
		draw();
		render.display();

		window.clear(sf::Color(0, 0, 0, 255));
		window.draw(renderSprite);
		window.display();
    }
}

void GameCore::update(void)
{

}

void GameCore::draw(void)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Magenta);
	render.draw(rect);
}

void GameCore::calcScale(void)
{
	sf::Vector2u size = window.getSize();

	unsigned int scaleX = size.x / renderSize.x;
	unsigned int scaleY = size.y / renderSize.y;
	scale = (scaleX <= scaleY) ? scaleX : scaleY;

	if (scale == 0)
	{
		scale = 1;
		renderOffset.x = 0;
		renderOffset.y = 0;

		window.setSize(renderSize);
		renderSprite.setScale(scale, scale);

		return;
	}
	else
		renderSprite.setScale(scale, scale);

	renderOffset.x = (size.x - (scale * renderSize.x)) / 2;
	renderOffset.y = (size.y - (scale * renderSize.y)) / 2;
	renderSprite.setPosition(renderOffset.x, renderOffset.y);
}