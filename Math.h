#ifndef __MATH_H__
#define __MATH_H__

#include <string>

using namespace std;

class Math
{
public:
	static string abs(const string& s);
	static bool isZero(const string& s);
	static string negative(const string& s);
	static bool isNegative(const string& s);
	static string trim(const string& s);
	static bool isGreaterThan(const string& n, const string& m);  // returns true if n > m else false
	static bool isGreaterThanOrEqual(const string& lhs, const string& rhs); // returns true if lhs >= rhs, false if rhs < lhs
	static string easyAdd(const string& lhs, const string rhs);
	static string add(const string& lhs, const string& rhs);
	static string easySubtract(const string& lhs, const string& rhs);
	static string subtract(const string& lhs, const string& rhs);
	static string easyMultiply(const string& lhs, const string& rhs);
	static string multiply(const string& lhs, const string& rhs);
	static string easyDivide(const string& lhs, const string& rhs);
	static string divide(const string& lhs, const string& rhs);
};

#endif
