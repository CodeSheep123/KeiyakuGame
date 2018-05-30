#include "Button.hpp"
#include <SFML\Window\Mouse.hpp>
#include "../../Global.hpp"

namespace Keiyaku
{
	namespace UI
	{
		Button::Button(std::string const& text, sf::Font const& font, Callback cb)
		{
			setString(text);
			setFont(font);
			callback() = cb;
		}
		
		void Button::setPosition(float width, float height) { m_shape.setPosition({ width, height }); }
		sf::Vector2f Button::getPosition() const { return m_shape.getPosition(); }

		void Button::setSize(float width, float height) { m_shape.setSize({ width, height }); }
		sf::Vector2f Button::getSize() const { return m_shape.getSize(); }

		void Button::setString(std::string const& str)
		{
			m_text.setString(str);
		}

		void Button::setFont(sf::Font const& font)
		{
			m_text.setFont(font);
		}

		sf::Text& Button::getText()
		{
			return m_text;
		}

		sf::Text const& Button::getText() const
		{
			return m_text;
		}

		typename Button::Callback& Button::callback()
		{
			return m_cb;
		}


		void Button::update()
		{
			//#TODO: Inside box check
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_currentlyPressed = true;
			}
			else
			{
				if (m_currentlyPressed)
				{
					//call callback on release
					m_cb();
				}

				m_currentlyPressed = false;
			}
		}

		void Button::draw()
		{
			gWindow->draw(m_shape);
			gWindow->draw(m_text);
		}
	}
}