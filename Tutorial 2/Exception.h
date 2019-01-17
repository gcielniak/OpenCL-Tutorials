#pragma once

#include <string>

class Exception
{
	std::string message;

public:
	Exception(const std::string s) : message(s) {};

	virtual const std::string& what() const throw() { return message; }
};

