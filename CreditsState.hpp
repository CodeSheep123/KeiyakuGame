#ifndef KEIYAKU_CREDITS_STATE_HPP_
#define KEIYAKU_CREDITS_STATE_HPP_

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
	};
}

#endif