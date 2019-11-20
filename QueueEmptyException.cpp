#include "QueueEmptyException.h"

QueueEmptyException::QueueEmptyException() : exception()
{
}

const char* QueueEmptyException::what() const throw()
{
	return "queue empty";
}