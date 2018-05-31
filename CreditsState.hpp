#ifndef KEIYAKU_CREDITS_STATE_HPP_
#define KEIYAKU_CREDITS_STATE_HPP_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "depend/resource_manager/FontManager.hpp"
#include "depend/resource_manager/MusicManager.hpp"
#include "depend/resource_manager/TextureManager.hpp"
#include "depend/ui/Button.hpp"

#include "GameState.hpp"

namespace Keiyaku
{
	class CreditsState : public GameState
	{
	public:
		virtual void onStart() override;
		virtual void onExit() override;

		virtual void update() override;
		virtual void draw() override;
	private:
		static constexpr int TitleXOffset = -20;
		static constexpr int TitleYOffset = -200;

		static constexpr int CreditsJobXOffset = -150;
		static constexpr int CreditsXSpacing = 270;
		static constexpr int ProgrammingCreditYOffset = -150;
		static constexpr int StoryCreditYOffset = -70;
		static constexpr int ArtCreditYOffset = 10;

		static constexpr int BackButtonYOffset = 250;


		/*Graphics*/
		sf::Sprite m_background;

		/*Audio*/
		MusicResource m_backgroundMusic;

		/*Text*/
		sf::Text m_titleText;
		
		struct Credit
		{
			sf::Text job;
			sf::Text name;

			void centerText(sf::Window* window, int xoffset, int yoffset, int xSpacing);
			void setDefaultTextStyle();
			void setText(std::string const& newJob, std::string const& newName);
		};

		Credit m_programmingCredit;
		Credit m_storyCredit;
		Credit m_artCredit;
		
		UI::Button m_backToMainButton;
	};
}

#endif