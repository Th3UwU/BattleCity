#include "gameCore.hpp"
GameCore* gameCore;

int main(void)
{
	gameCore = new GameCore();
	gameCore->loop();
	delete gameCore;

	return 0;
}