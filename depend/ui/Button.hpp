#ifndef KEIYAKU_BUTTON_HPP_
#define KEIYAKU_BUTTON_HPP_

#include "../../Entity.hpp"
#include <functional>
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

namespace Keiyaku
{
	namespace UI
	{

		class Button : public Entity
		{
		public:

			using Callback = std::function<void()>;

			Button() = default;
			Button(std::string const& text, sf::Font const& font, Callback cb);

			virtual void update() override;
			virtual void draw() override;

			void setString(std::string const& str);
			void setFont(sf::Font const& font);

			sf::Text& getText();
			sf::Text const& getText() const;

			void setSize(unsigned width, unsigned height);
			sf::Vector2f getSize() const;

			void setPosition(unsigned width, unsigned height);
			sf::Vector2f getPosition() const;

			Callback& callback();
		private:
			sf::Text m_text;
			sf::RectangleShape m_shape;

			Callback m_cb;
			bool m_currentlyPressed = false;
		};
	}
}

#endif