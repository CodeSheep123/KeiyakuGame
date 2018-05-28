#include "IGame.hpp"
#include "ErrorHandler.hpp"
#include "depend/logpp/log++.hpp"

#include <SFML\Window\Event.hpp>

#include <ctime>
#include <iomanip> //std::put_time
#include <sstream>

namespace Keiyaku
{
	IGame::~IGame() = default;

	void IGame::init(sf::VideoMode const& videomode, const char* title, bool fullscreen /* = false*/)
	{
		sf::Uint32 flags = sf::Style::Default;
		if (fullscreen) flags |= sf::Style::Fullscreen;

		m_window.create(videomode, title, flags);

		ErrorHandler::assert(m_window.isOpen(), "IGame::init(): Failed to create window");

		m_keybinds.load("default_keybinds.kbd");
	}

	void IGame::run()
	{
		/*Game starts*/
		onStart();

		m_window.setFramerateLimit(MAX_FPS);

		/*Main game loop*/
		while (m_window.isOpen())
		{
			/*Poll events*/
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed
					|| (event.type == sf::Event::KeyPressed && event.key.code == m_keybinds.getKey(Action::Exit)))
				{
					/*Exit event received*/
					m_window.close();
				}
			}

			update();

			m_window.clear();
			draw();

			m_window.display();
		}

		/*Game exits*/
		onExit();
	}

	void IGame::onStart()
	{
		//Override for customized behavior
	}

	void IGame::onExit()
	{
		//Override for customized behavior
	}

	void IGame::update()
	{
		//Override for customized behavior
	}
	
	void IGame::draw()
	{
		//Override for customized behavior
	}

	sf::RenderWindow* IGame::getWindow()
	{
		return &m_window;
	}

	KeybindManager* IGame::getKeybindManager()
	{
		return &m_keybinds;
	}

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(push) //This function uses deprecated capture() call. 
#pragma warning(disable: 4996)

	void IGame::makeScreenshot() const
	{
		auto img = m_window.capture();

		std::ostringstream name;
		name << "screenshots/Screenshot_";

		auto rawTime = std::time(nullptr);
		auto localTime = std::localtime(&rawTime);

		name << std::put_time(localTime, "%H-%M-%S");

		name << ".bmp";

		img.saveToFile(name.str());
	}

#pragma warning(pop)
}