#ifndef KEIYAKU_GAME_INTERFACE_HPP_
#define KEIYAKU_GAME_INTERFACE_HPP_

#include <SFML\Window\VideoMode.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

#include "KeyBindManager.hpp"

namespace Keiyaku
{
	class IGame
	{
	public:
		IGame() = default;
		IGame(IGame const& other) = delete;
		IGame(IGame&& other) = delete;

		IGame& operator=(IGame const& other) = delete;
		IGame& operator=(IGame&& other) = delete;

		virtual ~IGame();

		void run();
		void init(sf::VideoMode const& videomode, const char* title, bool fullscreen = false);

		sf::RenderWindow* getWindow();
		KeybindManager* getKeybindManager();

		static const long MAX_FPS = 120;

		void makeScreenshot() const;

	protected:
		virtual void onStart();
		virtual void onExit();
		virtual void update();
		virtual void draw();

	private:
		sf::RenderWindow m_window;
		KeybindManager m_keybinds;
	};
}

#endif //KEIYAKU_GAME_INTERFACE_HPP_