#include "CreditsState.hpp"

#include "Global.hpp"
#include "depend/logpp/log++.hpp"
#include "Utility.hpp"
#include "MainMenuState.hpp"

namespace Keiyaku
{
	void CreditsState::Credit::setText(std::string const& newJob, std::string const& newName)
	{
		job.setString(newJob);
		name.setString(newName);
	}

	void CreditsState::Credit::centerText(sf::Window* window, int xoffset, int yoffset, int xSpacing)
	{
		Utility::centerText(job, window, xoffset, yoffset);
		Utility::centerText(name, window, xoffset + xSpacing, yoffset);
	}

	void CreditsState::Credit::setDefaultTextStyle()
	{
		Utility::setDefaultTextStyle(job);
		Utility::setDefaultTextStyle(name);
	}

	void CreditsState::onStart()
	{
		logpp::Console::debug("Entering Credits");

		//#TemporaryArt
		m_backgroundMusic = gMusicManager->get(gPathDatabase->getPath("TEMP_background_music"));

		//#TemporaryArt
		m_background.setTexture(*gTextureManager->get(gPathDatabase->getPath("TEMP_title_back")));

		//#TemporaryArt
		Utility::setDefaultTextStyle(m_titleText);
		m_titleText.setString("Credits");

		//Center text
		auto windowSize = gWindow->getSize();
		auto windowMid = sf::Vector2u { windowSize.x / 2, windowSize.y / 2 };
		auto titleSize = m_titleText.getLocalBounds();
		m_titleText.setPosition((windowSize.x - titleSize.width) / 2 + TitleXOffset,
			(windowSize.y - titleSize.height) / 2 + TitleYOffset);

		//#TemporaryArt
		/*Programming Credit*/
		m_programmingCredit.setDefaultTextStyle();
		m_programmingCredit.setText("Programming", "NotAPenguin");
		m_programmingCredit.centerText(gWindow, CreditsJobXOffset, ProgrammingCreditYOffset, CreditsXSpacing);

		/*Story Credit*/
		m_storyCredit.setDefaultTextStyle();
		m_storyCredit.setText("Story writing", "Anakulos");
		m_storyCredit.centerText(gWindow, CreditsJobXOffset, StoryCreditYOffset, CreditsXSpacing);

		/*Art Credit*/
		m_artCredit.setDefaultTextStyle();
		m_artCredit.setText("Art", "Julicorn");
		m_artCredit.centerText(gWindow, CreditsJobXOffset, ArtCreditYOffset, CreditsXSpacing);

		//#TemporaryArt
		Utility::setDefaultButtonStyle(m_backToMainButton);
		m_backToMainButton.setString("Back");
		m_backToMainButton.setSize(200, 50);
		m_backToMainButton.setTextCentered(true);
		Utility::centerObject(m_backToMainButton, gWindow, 0, BackButtonYOffset);


		/*Go back to main menu*/
		m_backToMainButton.callback() = [this]() {getManager()->popState(std::make_shared<MainMenuState>()); };

		m_backgroundMusic->play();
	}

	void CreditsState::onExit()
	{
		m_backgroundMusic->stop();

		logpp::Console::debug("Exiting credits");
	}

	void CreditsState::update()
	{
		m_backToMainButton.update();
	}

	void CreditsState::draw()
	{
		//Draw background
		gWindow->draw(m_background);

		//Draw other elements
		gWindow->draw(m_titleText);
		gWindow->draw(m_programmingCredit.job);
		gWindow->draw(m_programmingCredit.name);
		gWindow->draw(m_storyCredit.job);
		gWindow->draw(m_storyCredit.name);
		gWindow->draw(m_artCredit.job);
		gWindow->draw(m_artCredit.name);
		
		m_backToMainButton.draw();
	}

}