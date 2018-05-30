#include "CreditsState.hpp"

#include "depend/logpp/log++.hpp"

namespace Keiyaku
{
	void CreditsState::onStart()
	{
		logpp::Console::debug("Entering Credits");
	}

	void CreditsState::onExit()
	{
		logpp::Console::debug("Exiting credits");
	}

	void CreditsState::update()
	{

	}

	void CreditsState::draw()
	{
		
	}
}