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

			sf::FloatRect getLocalBounds() const;

			void setTextCentered(bool center);

			sf::Text& getText();
			sf::Text const& getText() const;

			void setSize(float width, float height);
			sf::Vector2f getSize() const;

			void setPosition(float x, float y);
			sf::Vector2f getPosition() const;

			Callback& callback();
		protected:
			void centerText();
			void unCenterText();

		private:
			sf::Text m_text;
			sf::RectangleShape m_shape;
			sf::Rect<float> m_bounds;

			Callback m_cb;
			bool m_currentlyPressed = false;
			bool m_textCentered = false;
		};
	}
}

#endif