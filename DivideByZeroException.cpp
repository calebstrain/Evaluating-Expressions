#include "DivideByZeroException.h"
#include <stdexcept>

DivideByZeroException::DivideByZeroException() : exception()
{
}

const char* DivideByZeroException::what() const throw()
{
	return "divide by zero";
}