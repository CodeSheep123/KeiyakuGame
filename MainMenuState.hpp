#ifndef KEIYAKU_MAIN_MENU_STATE_HPP_
#define KEIYAKU_MAIN_MENU_STATE_HPP_

#include "GameState.hpp"
#include "depend/resource_manager/MusicManager.hpp"
#include "depend/resource_manager/FontManager.hpp"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

namespace Keiyaku
{
	class MainMenuState : public GameState
	{
	public:
		virtual ~MainMenuState();

		virtual void onStart() override;
		virtual void onExit() override;

		virtual void update() override;
		virtual void draw() override;
	private:
		/*Constants*/
		static constexpr int TitleYOffset = -200;
		static constexpr int TitleXOffset = -100;

		/*Resources*/
		MusicResource m_backgroundMusic;
		FontResource m_font;

		/*Actual drawable objects*/
		sf::Sprite m_background;
		sf::Text m_titleText;
	};
}

#endif