#include "ErrorHandler.hpp"
#include "depend/logpp/log++.hpp"


namespace Keiyaku
{

	void ErrorHandler::reportError(std::string_view message)
	{
#		ifdef KEIYAKU_DEBUG_BUILD
		logpp::Console::error(message);
#		endif //#ifdef KEIYAKU_DEBUG_BUILD
	}

	void ErrorHandler::assert(bool condition, std::string_view message)
	{
#		ifdef KEIYAKU_DEBUG_BUILD
		logpp::Console::assert(condition, message);
#		endif //#ifdef KEIYAKU_DEBUG_BUILD
	}


} //namespace Keiyaku

