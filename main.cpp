#include "Global.hpp"

#define FULLSCREEN false

#include "depend/logpp/log++.hpp"


int main()
{
#ifndef KEIYAKU_DEBUG_BUILD
	logpp::Console::disableDebug();
#endif
	Keiyaku::KeiyakuGame game;

	/*Initialize globals*/
	gGame = &game;
	gWindow = gGame->getWindow();
	gKeybindManager = gGame->getKeybindManager();

	gPathDatabase = &gGame->getPathDatabase();
	gTextureManager = &gGame->getTextureManager();
	gImageManager = &gGame->getImageManager();
	gFontManager = &gGame->getFontManager();
	gMusicManager = &gGame->getMusicManager();

	gGame->init(sf::VideoMode(800, 600), "Keiyaku!", FULLSCREEN);
	gGame->run();

	return 0;
}