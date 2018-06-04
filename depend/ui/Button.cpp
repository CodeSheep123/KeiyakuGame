#include "Button.hpp"
#include <SFML\Window\Mouse.hpp>
#include "../../Global.hpp"


#include "../logpp/log++.hpp"

namespace Keiyaku
{
	namespace UI
	{
		Button::Button(std::string const& text, sf::Font const& font, Callback cb)
		{
			setString(text);
			setFont(font);
			callback() = cb;
			m_bounds = m_shape.getGlobalBounds();
		}
		
		void Button::setPosition(float x, float y) 
		{ 
			m_shape.setPosition({ x, y }); 
			m_bounds = m_shape.getGlobalBounds();

			//re-center text
			m_textCentered ? centerText() : unCenterText();
		}
		sf::Vector2f Button::getPosition() const { return m_shape.getPosition(); }

		void Button::setSize(float width, float height) 
		{ 
			m_shape.setSize({ width, height });
			m_bounds = m_shape.getGlobalBounds(); 

			//re-center text
			m_textCentered ? centerText() : unCenterText();

		}
		sf::Vector2f Button::getSize() const { return m_shape.getSize(); }

		void Button::setString(std::string const& str)
		{
			m_text.setString(str);
		}

		void Button::setFont(sf::Font const& font)
		{
			m_text.setFont(font);
		}

		sf::FloatRect Button::getLocalBounds() const
		{
			return m_shape.getLocalBounds();
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
			auto mousePos = sf::Mouse::getPosition(*gWindow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_bounds.contains((float)mousePos.x, (float)mousePos.y))
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

		void Button::setTextCentered(bool center)
		{
			m_textCentered = center;
			
			center ? centerText() : unCenterText();
		}

		void Button::centerText()
		{
			static const int YOffset = -10; //small offset, because it will not accurately be centered otherwise

			auto textSize = m_text.getLocalBounds();
			auto x = m_bounds.left + (m_bounds.width - textSize.width) / 2;
			auto y = m_bounds.top + (m_bounds.height - textSize.height) / 2 + YOffset;
			m_text.setPosition(x, y);
		}

		void Button::unCenterText()
		{
			m_text.setPosition(m_bounds.left, m_bounds.top);
		}

		void Button::draw()
		{
			gWindow->draw(m_shape);
			gWindow->draw(m_text);
		}
	}
}