#ifndef KEIYAKU_UTILITY_HPP_
#define KEIYAKU_UTILITY_HPP_

#include <SFML/Graphics/Text.hpp>
#include "depend/ui/Button.hpp"

namespace Keiyaku
{
	namespace Utility
	{
		void setDefaultTextStyle(sf::Text& text);
		void centerText(sf::Text& text, sf::Window* window, int xoffset = 0, int yoffset = 0);

		void setDefaultButtonStyle(UI::Button& button);
		void centerButton(UI::Button& button, sf::Window* window, int xoffset = 0, int yoffset = 0);

		template<typename Object>
		void centerObject(Object& obj, sf::Window* window, int xoffset = 0, int yoffset = 0)
		{
			auto windowSize = window->getSize();
			auto windowMid = sf::Vector2u { windowSize.x / 2, windowSize.y / 2 };
			auto textSize = obj.getLocalBounds();
			obj.setPosition((windowSize.x - textSize.width) / 2 + xoffset,
				(windowSize.y - textSize.height) / 2 + yoffset);
		}
	}
}

#endif