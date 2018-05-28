#include "KeiyakuGame.hpp"
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "Global.hpp"

#include "depend/logpp/log++.hpp"
#include <memory>
#include <thread>

namespace Keiyaku
{
	KeiyakuGame::KeiyakuGame() : m_textureManager(&m_imageManager)
	{

	}

	void KeiyakuGame::onStart()
	{
		m_pathDatabase.load("paths.pd");

		m_stateManager.addState(std::make_shared<MainMenuState>());

		//Add the first state: A splash screen
		m_stateManager.addState(std::make_shared<SplashState>());
	}

	void KeiyakuGame::onExit()
	{
		
	}

	void KeiyakuGame::update()
	{

		if (sf::Keyboard::isKeyPressed(gKeybindManager->getKey(Action::Screenshot)))
		{
			makeScreenshot();
		}

		m_stateManager.update();
	}

	void KeiyakuGame::draw()
	{
		m_stateManager.draw();
	}

	TextureManager& KeiyakuGame::getTextureManager()
	{
		return m_textureManager;
	}

	ImageManager& KeiyakuGame::getImageManager()
	{
		return m_imageManager;
	}

	PathDatabase& KeiyakuGame::getPathDatabase()
	{
		return m_pathDatabase;
	}

	FontManager& KeiyakuGame::getFontManager()
	{
		return m_fontManager;
	}

	MusicManager& KeiyakuGame::getMusicManager()
	{
		return m_musicManager;
	}

}