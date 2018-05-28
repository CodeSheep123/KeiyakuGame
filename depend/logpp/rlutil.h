/*Library: rlutil

This is not written by me, so @Anakulos, dont bother to try to understand this, the code is absolutely terrible*/

#ifndef RLUTIL_H_
#define RLUTIL_H_

#define RLUTIL_INLINE inline

#include <iostream>
#include <string>


#ifdef _WIN32
	#include <windows.h>  // for WinAPI and Sleep()
	#define _NO_OLDNAMES  // for MinGW compatibility

#endif // _WIN32


namespace rlutil {


	using RLUTIL_STRING_T = std::string;

#define RLUTIL_PRINT(msg) do {std::cout << msg;} while(false);

enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};


 
const RLUTIL_STRING_T ANSI_CLS                = "\033[2J\033[3J";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_PRE  = "\033]0;";
const RLUTIL_STRING_T ANSI_CONSOLE_TITLE_POST = "\007";
const RLUTIL_STRING_T ANSI_ATTRIBUTE_RESET    = "\033[0m";
const RLUTIL_STRING_T ANSI_CURSOR_HIDE        = "\033[?25l";
const RLUTIL_STRING_T ANSI_CURSOR_SHOW        = "\033[?25h";
const RLUTIL_STRING_T ANSI_CURSOR_HOME        = "\033[H";
const RLUTIL_STRING_T ANSI_BLACK              = "\033[22;30m";
const RLUTIL_STRING_T ANSI_RED                = "\033[22;31m";
const RLUTIL_STRING_T ANSI_GREEN              = "\033[22;32m";
const RLUTIL_STRING_T ANSI_BROWN              = "\033[22;33m";
const RLUTIL_STRING_T ANSI_BLUE               = "\033[22;34m";
const RLUTIL_STRING_T ANSI_MAGENTA            = "\033[22;35m";
const RLUTIL_STRING_T ANSI_CYAN               = "\033[22;36m";
const RLUTIL_STRING_T ANSI_GREY               = "\033[22;37m";
const RLUTIL_STRING_T ANSI_DARKGREY           = "\033[01;30m";
const RLUTIL_STRING_T ANSI_LIGHTRED           = "\033[01;31m";
const RLUTIL_STRING_T ANSI_LIGHTGREEN         = "\033[01;32m";
const RLUTIL_STRING_T ANSI_YELLOW             = "\033[01;33m";
const RLUTIL_STRING_T ANSI_LIGHTBLUE          = "\033[01;34m";
const RLUTIL_STRING_T ANSI_LIGHTMAGENTA       = "\033[01;35m";
const RLUTIL_STRING_T ANSI_LIGHTCYAN          = "\033[01;36m";
const RLUTIL_STRING_T ANSI_WHITE              = "\033[01;37m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLACK   = "\033[40m";
const RLUTIL_STRING_T ANSI_BACKGROUND_RED     = "\033[41m";
const RLUTIL_STRING_T ANSI_BACKGROUND_GREEN   = "\033[42m";
const RLUTIL_STRING_T ANSI_BACKGROUND_YELLOW  = "\033[43m";
const RLUTIL_STRING_T ANSI_BACKGROUND_BLUE    = "\033[44m";
const RLUTIL_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
const RLUTIL_STRING_T ANSI_BACKGROUND_CYAN    = "\033[46m";
const RLUTIL_STRING_T ANSI_BACKGROUND_WHITE   = "\033[47m";


RLUTIL_INLINE RLUTIL_STRING_T getANSIColor(const int c) {
	switch (c) {
		case BLACK       : return ANSI_BLACK;
		case BLUE        : return ANSI_BLUE; // non-ANSI
		case GREEN       : return ANSI_GREEN;
		case CYAN        : return ANSI_CYAN; // non-ANSI
		case RED         : return ANSI_RED; // non-ANSI
		case MAGENTA     : return ANSI_MAGENTA;
		case BROWN       : return ANSI_BROWN;
		case GREY        : return ANSI_GREY;
		case DARKGREY    : return ANSI_DARKGREY;
		case LIGHTBLUE   : return ANSI_LIGHTBLUE; // non-ANSI
		case LIGHTGREEN  : return ANSI_LIGHTGREEN;
		case LIGHTCYAN   : return ANSI_LIGHTCYAN; // non-ANSI;
		case LIGHTRED    : return ANSI_LIGHTRED; // non-ANSI;
		case LIGHTMAGENTA: return ANSI_LIGHTMAGENTA;
		case YELLOW      : return ANSI_YELLOW; // non-ANSI
		case WHITE       : return ANSI_WHITE;
		default: return "";
	}
}


RLUTIL_INLINE RLUTIL_STRING_T getANSIBackgroundColor(const int c) {
	switch (c) {
		case BLACK  : return ANSI_BACKGROUND_BLACK;
		case BLUE   : return ANSI_BACKGROUND_BLUE;
		case GREEN  : return ANSI_BACKGROUND_GREEN;
		case CYAN   : return ANSI_BACKGROUND_CYAN;
		case RED    : return ANSI_BACKGROUND_RED;
		case MAGENTA: return ANSI_BACKGROUND_MAGENTA;
		case BROWN  : return ANSI_BACKGROUND_YELLOW;
		case GREY   : return ANSI_BACKGROUND_WHITE;
		default: return "";
	}
}


RLUTIL_INLINE void setColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c); // Foreground colors take up the least significant byte
#else
	RLUTIL_PRINT(getANSIColor(c));
#endif
}

/// Function: setBackgroundColor
/// Change background color specified by number (Windows / QBasic colors).
/// Don't change the foreground color
///
/// See <Color Codes>
RLUTIL_INLINE void setBackgroundColor(int c) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hConsole, &csbi);

	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFF0F) | (((WORD)c) << 4)); // Background colors take up the second-least significant byte
#else
	RLUTIL_PRINT(getANSIBackgroundColor(c));
#endif
}

RLUTIL_INLINE int saveDefaultColor() {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	static char initialized = 0; // bool
	static WORD attributes;

	if (!initialized) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		attributes = csbi.wAttributes;
		initialized = 1;
	}
	return (int)attributes;
#else
	return -1;
#endif
}

RLUTIL_INLINE void resetColor(void) {
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)saveDefaultColor());
#else
	RLUTIL_PRINT(ANSI_ATTRIBUTE_RESET);
#endif
}

}; // namespace rlutil


#undef RLUTIL_INLINE
#undef RLUTIL_PRINT

#endif
