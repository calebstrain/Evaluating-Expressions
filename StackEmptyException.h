#ifndef __STACKEMPTYEXCEPTION_H__
#define __STACKEMPTYEXCEPTION_H__

#include <exception>
using namespace std;

class StackEmptyException : public exception
{
public:
	StackEmptyException();
	virtual const char* what() const throw();
};

#endif
