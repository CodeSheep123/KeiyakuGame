#ifndef KEIYAKU_KEIYAKU_GAME_HPP_
#define KEIYAKU_KEIYAKU_GAME_HPP_

#include "IGame.hpp"
#include "GameStateManager.hpp"
#include "depend/resource_manager/ImageManager.hpp"
#include "depend/resource_manager/TextureManager.hpp"
#include "depend/resource_manager/PathDatabase.hpp"
#include "depend/resource_manager/FontManager.hpp"
#include "depend/resource_manager/MusicManager.hpp"

namespace Keiyaku
{
	class KeiyakuGame : public IGame
	{
	public:
		KeiyakuGame();
		~KeiyakuGame() = default;

		void onStart() override;
		void onExit() override;

		void update() override;
		void draw() override;

		ImageManager& getImageManager();
		TextureManager& getTextureManager();
		PathDatabase& getPathDatabase();
		FontManager& getFontManager();
		MusicManager& getMusicManager();

	private:
		GameStateManager m_stateManager;
		ImageManager m_imageManager;
		TextureManager m_textureManager;
		PathDatabase m_pathDatabase;
		FontManager m_fontManager;
		MusicManager m_musicManager;
	};
}

#endif