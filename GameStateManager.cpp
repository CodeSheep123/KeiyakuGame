#include "GameStateManager.hpp"

#include "GameState.hpp"
#include "depend/logpp/log++.hpp"

namespace Keiyaku
{
	GameStateManager::~GameStateManager()
	{
		while (!m_states.empty())
		{
			m_states.pop();
		}
	}

	void GameStateManager::addState(std::shared_ptr<GameState> state)
	{
		m_states.push(state);
		m_states.top()->setManager(this);
//		m_states.top()->onStart();
	}

	void GameStateManager::popState()
	{
		if (m_states.empty())
		{
			logpp::Console::warning("GameStateManager::popState(): State stack is empty");
			return;
		}
		m_states.top()->onExit();
		m_states.pop();
	}

	void GameStateManager::popState(std::shared_ptr<GameState> nextState)
	{
		popState();
		addState(nextState);
	}

	void GameStateManager::update()
	{
		if (m_states.empty())
		{
			logpp::Console::warning("GameStateManager::update(): State stack is empty");
			return;
		}
		if (!m_states.top()->isStarted()) m_states.top()->start();
		m_states.top()->update();
	}

	void GameStateManager::draw()
	{
		if (m_states.empty())
		{
			logpp::Console::warning("GameStateManager::draw(): State stack is empty");
			return;
		}
		m_states.top()->draw();
	}
}