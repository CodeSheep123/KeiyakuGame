#ifndef KEIYAKU_SPLASH_STATE_HPP_
#define KEIYAKU_SPLASH_STATE_HPP_

#include "GameState.hpp"
#include "depend/resource_manager/MusicManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Keiyaku
{
	class SplashState : public GameState
	{
	public:
		virtual ~SplashState();

		virtual void onStart() override;
		virtual void onExit() override;

		virtual void update() override;
		virtual void draw() override;
	private:
		sf::Sprite m_background;
		sf::Text m_titleText;
		sf::Text m_pressSpaceText;

		MusicResource m_backMusic;
	};
}

#endif