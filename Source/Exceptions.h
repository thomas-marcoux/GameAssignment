#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

#define BAD_SPRITE "Sprite not found."
#define LOAD_ERROR "File does not exist."
#define PARSE_ERROR	"File has been corrupted."

class LoadException : public std::exception
{
public:
	LoadException(std::string s) : msg(s) {}
	~LoadException() {}
	std::string getMsg() { return msg; }

private:
	std::string msg;
};

#endif // !EXCEPTIONS_H
