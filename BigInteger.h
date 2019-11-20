#ifndef __BIGINTEGER_H__
#define __BIGINTEGER_H__

#include <string>
#include <stdexcept>
using namespace std;

class BigInteger
{
private:
	string value;
	string validate(const string& s);
public:
	BigInteger();
	BigInteger(const BigInteger& n);
	BigInteger(const string& s);
	explicit operator const char*() const;
	BigInteger operator+(const BigInteger& rhs) const;
};

#endif