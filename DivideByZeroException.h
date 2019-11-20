#ifndef __DIVIDEBYZEROEXCEPTION_H__
#define __DIVIDEBYZEROEXCEPTION_H__
#include <exception>
using namespace std;

class DivideByZeroException : public exception
{
public:
	DivideByZeroException();
	virtual const char* what() const throw();

};

#endif
