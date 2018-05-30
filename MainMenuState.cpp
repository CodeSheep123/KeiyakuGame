#include "MainMenuState.hpp"

#include "depend/logpp/log++.hpp"
#include "depend/resource_manager/TextureManager.hpp"

#include "Global.hpp"

namespace Keiyaku
{
	MainMenuState::~MainMenuState()
	{

	}

	void MainMenuState::onStart()
	{
		logpp::Console::debug("Entering main menu");

		//#TemporaryArt
		m_backgroundMusic = gMusicManager->get(gPathDatabase->getPath("TEMP_background_music"));
		//#TemporaryArt
		m_background.setTexture(*gTextureManager->get(gPathDatabase->getPath("TEMP_title_back")));
		//#TemporaryArt
		m_font = gFontManager->get(gPathDatabase->getPath("TEMP_title_font"));

		m_titleText.setFont(*m_font);
		m_titleText.setString("Keiyaku!");
		//#TemporaryArt
		m_titleText.setFillColor(sf::Color::Green);
		
		/*Position text*/
		auto windowSize = gWindow->getSize();
		auto titleSize = m_titleText.getLocalBounds();
		m_titleText.setPosition((windowSize.x - titleSize.width) / 2 + TitleXOffset, 
			(windowSize.y - titleSize.height) / 2 + TitleYOffset);

		m_startButton.setString("Say Hi");
		m_startButton.callback() = [this]() {sayHi(); };

		m_backgroundMusic->play();
	}

	void MainMenuState::onExit()
	{
		logpp::Console::debug("Exiting main menu");
		m_backgroundMusic->stop();
	}

	void MainMenuState::update()
	{
		m_startButton.update();
	}

	void MainMenuState::draw()
	{
		m_startButton.draw();

		gWindow->draw(m_background);
		gWindow->draw(m_titleText);
	}
}