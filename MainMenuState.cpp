#include "MainMenuState.hpp"
#include "CreditsState.hpp"

#include "depend/logpp/log++.hpp"
#include "depend/resource_manager/TextureManager.hpp"

#include "Global.hpp"

namespace Keiyaku
{
	MainMenuState::~MainMenuState()
	{

	}
#pragma warning(push)
#pragma warning(disable: 4244) //C4244: Conversion from unsigned int to float, possible loss of data
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
		auto windowMid = sf::Vector2u{ windowSize.x / 2, windowSize.y / 2 };
		auto titleSize = m_titleText.getLocalBounds();
		m_titleText.setPosition((windowSize.x - titleSize.width) / 2 + TitleXOffset, 
			(windowSize.y - titleSize.height) / 2 + TitleYOffset);

		//#TemporaryArt
		m_startButton.setString("Start Game");
		m_startButton.callback() = [this]() { startGame(); };
		m_startButton.getText().setFont(*m_font);
		m_startButton.setPosition(windowMid.x + ButtonXOffset, windowMid.y + StartButtonYOffset);
		m_startButton.setSize(200, 50);
		m_startButton.getText().setFillColor(sf::Color::Green);
		m_startButton.setTextCentered(true);

		//#TemporaryArt
		m_quitButton.setString("Quit");
		m_quitButton.callback() = []() {gGame->end(); };
		m_quitButton.getText().setFont(*m_font);
		logpp::Console::debug(std::to_string(windowMid.x + ButtonXOffset) + std::to_string(windowMid.y + QuitButtonYOffset));
		m_quitButton.setPosition(windowMid.x + ButtonXOffset, windowMid.y + QuitButtonYOffset);
		m_quitButton.setSize(200, 50);
		m_quitButton.getText().setFillColor(sf::Color::Green);
		m_quitButton.setTextCentered(true);

		//#TemporaryArt
		m_creditsButton.setString("Credits");
		/*Go to next state: Credits state*/
		m_creditsButton.callback() = [this]() {getManager()->popState(std::make_shared<CreditsState>()); };

		m_backgroundMusic->play();
	}
#pragma warning(pop)

	void MainMenuState::onExit()
	{
		logpp::Console::debug("Exiting main menu");
		m_backgroundMusic->stop();
	}

	void MainMenuState::update()
	{
		m_startButton.update();
		m_quitButton.update();
	}

	void MainMenuState::draw()
	{
		gWindow->draw(m_background);
		gWindow->draw(m_titleText);

		m_startButton.draw();
		m_quitButton.draw();
	}

	void MainMenuState::startGame()
	{
		logpp::Console::debug("Starting game");
	}
}