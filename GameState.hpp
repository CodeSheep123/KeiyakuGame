#ifndef KEIYAKU_GAME_STATE_HPP_
#define KEIYAKU_GAME_STATE_HPP_

#include <memory>

namespace Keiyaku
{
	class GameStateManager;

	class GameState
	{
	public:
		GameState() = default;
		virtual ~GameState();

		void setManager(GameStateManager* m);
		GameStateManager* getManager();

		virtual void onStart();
		virtual void onExit();

		virtual void update();
		virtual void draw();

		bool isStarted();
		void start();

	protected:
		void end();
		void end(std::shared_ptr<GameState> nextState);

	private:
		GameStateManager * m_manager = nullptr;
		bool m_started = false;
	};
}

#endif