#ifndef LOG_PLUS_PLUS_HPP
#define LOG_PLUS_PLUS_HPP


#include <iostream> //for logging to the Console
#include <string_view>
#include <fstream> //for TextFile class


namespace logpp
{
	/*Class for writing colored and formatted output to the console. This class never throws exceptions*/
	class Console final
	{
	public:
		/*Prevent instantiation*/
		Console() = delete;

		/*Color enum*/
		enum Color
		{
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


		/*Static logging functions*/

		/*prints error message when condition parameter is false*/
		static void assert(bool condition, std::string_view text, Color clr = Color::LIGHTRED);
		/*Prints a light red error message*/
		static void error(std::string_view text, Color clr = Color::LIGHTRED);
		/*Prints a light green debug message.*/
		static void debug(std::string_view text, Color clr = Color::LIGHTGREEN);
		/*Prints a yellow warning message*/
		static void warning(std::string_view text, Color clr = Color::YELLOW);
		/*Prints a white log message*/
		static void log(std::string_view text, Color clr = m_defaultColor);

		/*Sets default color for log and debug messages*/
		static void setDefaultColor(Color clr);

		/*Disables debugging output*/
		static void disableDebug();

		/*Enables debug*/
		static void enableDebug();

	private:
		static Color m_defaultColor;
		static bool m_debuggingEnabled;

	};

	class TextFile final
	{
	public:
		//Create empty text file
		TextFile();
		//Automatically closes the file if it is open, doesn't throw exceptions
		~TextFile();

		/*<param name="path">The path of the file to open</param>
		  <param name="allow_create">If true, create() will be called to open the file, thus allowing a new file to be created. Defaults to false</param>
		  <exception cref="TextFile::Exception">Thrown when fstream::open fails</exception>*/
		explicit TextFile(std::string_view path, bool allow_create = false);

		//Opens a file, this function requires the file to exist, and wil throw an exception of type TextFile::Exception if the file doesn't exist
		void open(std::string_view path);
		//Creates and opens a new file at specified path. Throws an exception of type TextFile::Exception when creation fails
		void create(std::string_view path);

		//Closes the file. If no file is currently open, this function will throw an exception of type TextFile::Exception
		void close();

		//Writes data to current position in the textfile. Throws an exception of type TextFile::Exception when no file is opened
		void write(std::string_view text);

		//Moves the cursor to specified location. 0 for start. Throws an exception of type TextFile::Exception when no file is opened
		void moveCursor(long pos);

		//Gets the current cursor position. Throws an exception of type TextFile::Exception when no file is opened
		auto getCursor();

		//Returns true if a file is currently opened
		bool isOpen();

		///Exceptions thrown by TextFile class will be of this type
		class Exception final
		{
		private:
			std::string error;
		public:
			explicit Exception(std::string_view msg);

			///<returns>Returns an std::string describing the error</returns>
			std::string_view what();
		};

	private:
		std::fstream file;
	};

	class FileLog final
	{
	public:
		/*Creates an empty log, doesn't open a file for writing*/
		FileLog();

		/*Opens a log at path fileName*/
		explicit FileLog(std::string_view fileName, bool timestamp = true);

		/*Closes the logging file*/
		~FileLog();

		/*Opens a log at path fileName*/
		void open(std::string_view fileName, bool timestamp = true);

		/*Closes current logging file*/
		void close();

		/*Writes text to current logging file. Throws an instance of FileLog::Exception when there is currently no log open.
		 *Automatically adds a newline*/
		void write(std::string_view text, bool timestamp = true);

		/*Returns true if there is currently a file open for logging*/
		bool isOpen();

		/*Class used for exceptions in FileLog*/
		class Exception final
		{
		public:
			explicit Exception(std::string_view msg);

			///<returns>An std::string describing the error</returns>
			std::string_view what();
		private:
			std::string error; 
		};

	private:
		TextFile file;
		std::string generateTimeStamp();
	};
}
#endif