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
	}
}

#endif