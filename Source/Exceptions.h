#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

//Error messages
#define NO_SPRITE "Sprite not found: "
#define NO_COMPONENT "Sprite Component failed to load."
#define LOAD_ERROR "File does not exist: "
#define PARSE_ERROR	"File has been corrupted: "

//Exception class for loading files
class LoadException : public std::exception
{
public:
	LoadException(std::string s, std::string file = "") : msg(s+file) {}
	~LoadException() {}
	std::string getMsg() { return msg; }

private:
	std::string msg;
};

#endif // !EXCEPTIONS_H
