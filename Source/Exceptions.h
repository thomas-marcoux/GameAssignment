#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <iostream>

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
