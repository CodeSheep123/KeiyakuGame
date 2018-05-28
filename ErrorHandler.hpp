#ifndef KEIYAKU_ERROR_HANDLER_HPP_
#define KEIYAKU_ERROR_HANDLER_HPP_

#include <string_view>

namespace Keiyaku
{

	class ErrorHandler
	{
	public:
		//Everything will be done though static methods, so we delete the constructor
		ErrorHandler() = delete;

		/*reports an error to the output stream, that defaults to std::cerr*/
		static void reportError(std::string_view message);

		static void assert(bool condition, std::string_view message);
	};

} //namespace Keiyaku

#endif //#ifndef KEIYAKU_ERROR_HANDLER_HPP_