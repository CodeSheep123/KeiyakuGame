#include "SplashState.hpp"
#include "Global.hpp"

#include "depend/logpp/log++.hpp"


namespace Keiyaku
{
	SplashState::~SplashState()
	{
	
	}

	void SplashState::onStart()
	{
		/*Set title font, text and size*/
		 
		auto font = gFontManager->get(gPathDatabase->getPath("TEMP_title_font"));

		m_titleText.setFont(*font);
		m_titleText.setString("Keiyaku!");
		m_titleText.setCharacterSize(60);

		/*Center text*/
		auto windowSize = gWindow->getSize();
		auto textSize = m_titleText.getLocalBounds();
		m_titleText.setPosition((windowSize.x - textSize.width) / 2, (windowSize.y - textSize.height) / 2);

		m_pressSpaceText.setFont(*font);
		m_pressSpaceText.setString("Press SPACE to start...");
		m_pressSpaceText.setCharacterSize(18);

		/*Center text below title*/
		auto spaceTextSize = m_pressSpaceText.getLocalBounds();
		auto titlePos = m_titleText.getPosition();

		/*Make sure that the text is centered. We do this by calculating the difference in width between the two texts 
		 *and then adding this to our position*/
		auto xdiff = textSize.width - spaceTextSize.width;
		static const float YOFFSET = 10;

		m_pressSpaceText.setPosition(titlePos.x + xdiff / 2, titlePos.y + textSize.height + YOFFSET);

		/*Set background*/
		m_background.setTexture(*gTextureManager->get(gPathDatabase->getPath("TEMP_title_back")));
	}

	void SplashState::onExit()
	{

	}

	void SplashState::update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			end();
		}
	}

	void SplashState::draw()
	{
		//First draw background
		gWindow->draw(m_background);
		gWindow->draw(m_titleText);
		gWindow->draw(m_pressSpaceText);
	}
}