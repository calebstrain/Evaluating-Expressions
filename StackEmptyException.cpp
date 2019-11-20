#include "StackEmptyException.h"
#include <stdexcept>

StackEmptyException::StackEmptyException() : exception()
{
}

const char* StackEmptyException::what() const throw()
{
	return "stack empty";
}