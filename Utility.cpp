#include "Utility.hpp"

#include "Global.hpp"

namespace Keiyaku::Utility
{
	void setDefaultTextStyle(sf::Text& text)
	{
		static FontResource defaultFont = gFontManager->get(gPathDatabase->getPath("TEMP_title_font"));
		static sf::Color defaultColor = sf::Color::Green;

		text.setFont(*defaultFont);
		text.setFillColor(defaultColor);
	}

	void centerText(sf::Text& text, sf::Window* window, int xoffset /* = 0 */, int yoffset /* = 0 */)
	{
		auto windowSize = window->getSize();
		auto windowMid = sf::Vector2u { windowSize.x / 2, windowSize.y / 2 };
		auto textSize = text.getLocalBounds();
		text.setPosition((windowSize.x - textSize.width) / 2 + xoffset,
			(windowSize.y - textSize.height) / 2 + yoffset);
	}

	void setDefaultButtonStyle(UI::Button& button)
	{
		static FontResource defaultFont = gFontManager->get(gPathDatabase->getPath("TEMP_title_font"));
		static sf::Color defaultColor = sf::Color::Green;

		button.setFont(*defaultFont);
		button.getText().setFillColor(defaultColor);
	}

	void centerButton(UI::Button& button, sf::Window* window, int xoffset /* = 0 */, int yoffset /* = 0 */)
	{
		auto windowSize = window->getSize();
		auto windowMid = sf::Vector2u { windowSize.x / 2, windowSize.y / 2 };
		auto buttonSize = button.getSize();
		button.setPosition((windowSize.x - buttonSize.x) / 2 + xoffset,
			(windowSize.y - buttonSize.y) / 2 + yoffset);
	}
}