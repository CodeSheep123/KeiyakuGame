#include "GameState.hpp"
#include "ErrorHandler.hpp"
#include "GameStateManager.hpp"

namespace Keiyaku
{
	GameState::~GameState()
	{
	}

	void GameState::onStart()
	{
	}

	void GameState::onExit()
	{
	}

	void GameState::update()
	{

	}

	void GameState::draw()
	{

	}

	void GameState::end()
	{
		m_manager->popState();
	}

	void GameState::end(std::shared_ptr<GameState> nextState)
	{
		m_manager->popState(nextState);
	}

	void GameState::setManager(GameStateManager* m)
	{
		ErrorHandler::assert(m != nullptr, "GameState::setManager(): Manager was nullptr");
		m_manager = m;
	}

	GameStateManager* GameState::getManager()
	{
		return m_manager;
	}

	bool GameState::isStarted()
	{
		return m_started;
	}

	void GameState::start()
	{
		m_started = true;
		onStart();
	}
}