#ifndef KEIYAKU_GAME_STATE_MANAGER_HPP_
#define KEIYAKU_GAME_STATE_MANAGER_HPP_

#include <memory>
#include <stack>

namespace Keiyaku
{
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager() = default;
		~GameStateManager();

		void addState(std::shared_ptr<GameState> state);
		void popState();
		void popState(std::shared_ptr<GameState> nextState);

		void update();
		void draw();
	private:
		std::stack<std::shared_ptr<GameState>> m_states;
	};
}

#endif