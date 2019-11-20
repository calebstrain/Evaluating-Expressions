#ifndef __QUEUEEMPTYEXCEPTION_H__
#define __QUEUEEMPTYEXCEPTION_H__

#include <exception>
using namespace std;

class QueueEmptyException : public exception
{
public:
	QueueEmptyException();
	virtual const char* what() const throw();
};
#endif
