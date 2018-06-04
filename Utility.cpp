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

	//This function is kept for compatibility
	void centerText(sf::Text& text, sf::Window* window, int xoffset /* = 0 */, int yoffset /* = 0 */)
	{
		centerObject(text, window, xoffset, yoffset);
	}

	void setDefaultButtonStyle(UI::Button& button)
	{
		static FontResource defaultFont = gFontManager->get(gPathDatabase->getPath("TEMP_title_font"));
		static sf::Color defaultColor = sf::Color::Green;

		button.setFont(*defaultFont);
		button.getText().setFillColor(defaultColor);
	}

	//This function is kept for compatibility
	void centerButton(UI::Button& button, sf::Window* window, int xoffset /* = 0 */, int yoffset /* = 0 */)
	{
		centerObject(button, window, xoffset, yoffset);
	}
}