#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <ostream>
#include <string>

enum class LogType
{
	LOG,
	WARN,
	ERROR,
	FATAL
};

class Print
{
public:

	template <typename... Args>
	static void PrintLog(LogType logType, Args ... args)
	{
		std::cout << _EnumToString(logType) << " - ";
		_DoPrint(std::cout, args...);
		std::cout << std::endl;
	}

	template <typename... Args>
	static void PrintLog(Args ... args)
	{
		std::cout << _EnumToString(LogType::LOG) << " - ";
		_DoPrint(std::cout, args...);
		std::cout << std::endl;
	}

private:
	static std::string _EnumToString(LogType logType)
	{
		switch (logType)
		{
		case LogType::LOG: return "LOG";
		case LogType::WARN: return "WARN";
		case LogType::ERROR: return "ERROR";
		case LogType::FATAL: return "FATAL";
		}
		return "LOG";
	}

	template <typename Arg, typename... Args>
	static void _DoPrint(std::ostream& out, Arg&& arg, Args&&... args)
	{
		out << std::forward<Arg>(arg);
		using expander = int[];
		(void)expander {
			0, (void(out << std::forward<Args>(args)), 0)...
		};
	}
};

#endif //PRINT_H