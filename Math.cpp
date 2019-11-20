#include <string>
#include "Math.h"
#include "Queue.h"
#include "QueueEmptyException.h"
#include "DivideByZeroException.h"
#include <stdexcept>

using namespace std;

string Math::abs(const string& s)
{
	int len = s.length();
	if (len < 1) // should never happen
		throw invalid_argument("empty string");
	if (s[0] == '-')
	{
		if (len == 1) // should never happen
			throw invalid_argument("minus sign without a number");
		return s.substr(1, s.length() - 1);
	}
	if (s[0] == '+') // should never happen
	{
		if (len == 1)
			throw invalid_argument("plus sign without a number");
		return s.substr(1, s.length() - 1);
	}
	return s;
}
bool Math::isZero(const string& s)
{
	int len = s.length();
	if (len < 1)
		throw invalid_argument("empty string");
	int start = 0;
	if (s[0] == '+')
		start = 1;
	for (int i = start; i < len; i++)
		if (s[i] != '0')
			return false;
	return true;
}
string Math::negative(const string& s)
{
	int len = s.length();
	if (len < 1) // should never happen
		throw invalid_argument("empty string");
	if (s[0] == '-')
	{
		if (len == 1) // should never happen
			throw invalid_argument("minus sign without a number");
		return s.substr(1, s.length() - 1);
	}
	if (s[0] == '+') // should never happen
	{
		if (len == 1)
			throw invalid_argument("plus sign without a number");
		return "-" + s.substr(1, s.length() - 1);
	}
	if (isZero(s))
		return "0";
	return "-" + s;
}
bool Math::isNegative(const string& s)
{
	int len = s.length();
	if (len == 0) // should never happen
		throw invalid_argument("empty string");
	if (s[0] == '-')
	{
		if (len == 1) // should never happen
			throw invalid_argument("minus sign without a number");
		return true;
	}
	if (s[0] == '+') // should never happen
	{
		if (len == 1) // should never happen
			throw invalid_argument("plus sign without a number");
		return false;
	}
	return false;
}
string Math::trim(const string& s)
{
	int len = s.length();
	if (len == 0)
		throw invalid_argument("empty string");
	int start = 0;
	bool minus = false;
	if (s[0] == '-')
	{
		if (len < 2) // should never happen
			throw invalid_argument("minus sign without a number");
		start = 1;
		minus = true;
	}
	else if (s[0] == '+') // should never happen
	{
		if (len < 2) // should never happen
			throw invalid_argument("plus sign without a number");
		start = 1;
	}

	int end = start;
	while (s[end] == '0' && end < len)
		if (s[end] == '0')
			end++;

	if (end == len)
		return "0";
	if (start == 0)
		return s.substr(end, len - end - start);
	if (minus)
		return "-" + s.substr(end, len - end - start + 1);
	return s.substr(end, len - end - start + 1);
}
bool Math::isGreaterThan(const string& n, const string& m)  // returns true if n > m else false
{
	try
	{
		string nTrim = trim(n);
		string mTrim = trim(m);

		if (isNegative(nTrim))
		{
			if (isNegative(mTrim)) // both negative; do compare
			{
				int nTrimLen = nTrim.length();
				int mTrimLen = mTrim.length();
				if (nTrimLen < mTrimLen)
					return true;
				if (nTrimLen > mTrimLen)
					return false;
				int i = 1;
				while (i < nTrimLen && i < mTrimLen)
				{
					if (nTrim[i] < mTrim[i])
						return true;
					if (nTrim[i] > mTrim[i])
						return false;
					i++;
				}
				return false; // equal
			}
			return false; // n is -ve, m is +ve.  n cannot be greater than m
		}
		else
		{
			if (isNegative(mTrim)) // n is +ve, n is -ve.  n must be greather than m
				return true;
			// both n and m are +ve; do compare
			int nTrimLen = nTrim.length();
			int mTrimLen = mTrim.length();
			if (nTrimLen < mTrimLen)
				return false;
			if (nTrimLen > mTrimLen)
				return true;
			int i = 0;
			while (i < nTrimLen && i < mTrimLen)
			{
				if (nTrim[i] < mTrim[i])
					return false;
				if (nTrim[i] > mTrim[i])
					return true;
				i++;
			}
			return false; // equal
		}
	}
	catch (...)
	{
	}
	return false;
}
bool Math::isGreaterThanOrEqual(const string& lhs, const string& rhs) // returns true if lhs >= rhs, false if rhs < lhs
{
	try
	{
		string lhst = trim(lhs);
		string rhst = trim(rhs);

		if (isNegative(lhst))
		{
			if (isNegative(rhst)) // both negative; do compare
			{
				int lhstl = lhst.length();
				int rhstl = rhst.length();
				if (lhstl < rhstl)
					return true;
				if (lhstl > rhstl)
					return false;
				int i = 1;
				while (i < lhstl && i < rhstl)
				{
					if (lhst[i] < rhst[i])
						return true;
					if (lhst[i] > rhst[i])
						return false;
					i++;
				}
				return true; // equal
			}
			return false; // lhs is -ve, rhs is +ve.  lhs cannot be greater than rhs
		}
		else
		{
			if (isNegative(rhst)) // lhs is +ve, rhs is -ve.  lhs must be greather than rhs
				return true;
			// both lhs and rhs are +ve; do compare
			int lhstl = lhst.length();
			int rhstl = rhst.length();
			if (lhstl < rhstl)
				return false;
			if (lhstl > rhstl)
				return true;
			int i = 0;
			while (i < lhstl && i < rhstl)
			{
				if (lhst[i] < rhst[i])
					return false;
				if (lhst[i] > rhst[i])
					return true;
				i++;
			}
			return true; // equal
		}
	}
	catch (...)
	{
	}
	return false;
}
string Math::easyAdd(const string& lhs, const string rhs)
{
	try
	{
		int i = lhs.length() - 1;
		int j = rhs.length() - 1;

		if (i < 0)
			throw invalid_argument("lhs is the empty string");
		if (j < 0)
			throw invalid_argument("rhs is the emptyh string");

		string result = "";
		char ic;
		char jc;
		int n;
		int carry = 0;
		while (i >= 0 || j >= 0)
		{
			ic = (i >= 0) ? (lhs[i]) : ('0');
			jc = (j >= 0) ? (rhs[j]) : ('0');

			if (ic <'0' || ic>'9')
				throw invalid_argument("lhs contains at least one not in [0,1, 2, ..., 9]");
			if (jc <'0' || jc>'9')
				throw invalid_argument("rhs contains at least one not in [0,1, 2, ..., 9]");

			n = ((int)ic - (int)'0') + ((int)jc - (int)'0') + carry;
			if (n >= 10)
			{
				n -= 10;
				carry = 1;
			}
			else
			{
				carry = 0;
			}
			result = ((char)(n + (int)'0')) + result;
			i--;
			j--;
		}
		if (carry)
			result = "1" + result;
		else
			result = trim(result);
		return result;
	}
	catch (...)
	{
		throw;
	}
}
string Math::add(const string& lhs, const string& rhs)
{
	string tempLhs;
	string tempRhs;
	bool makeNegative = false;

	if (isNegative(lhs))
	{
		if (isNegative(rhs)) // both lhs & rhs are -ve.  do addition with absolute values and then reverse the sign on the result
		{
			tempLhs = abs(lhs);
			tempRhs = abs(rhs);
			makeNegative = true;
		}
		else // lhs is -ve, rhs is +ve.  do substraction instead with +ve numbers where lhs >= rhs
		{
			string absLhs = abs(lhs);
			if (isGreaterThan(absLhs, rhs))
				return negative(subtract(absLhs, rhs));
			return subtract(rhs, absLhs);
		}
	}
	else
	{
		if (isNegative(rhs)) // lhs is +ve, rhs is -ve.  do subtraction instead with +ve numbers where lhs >= rhs
		{
			string absRhs = abs(rhs);
			if (isGreaterThan(lhs, absRhs))
				return subtract(lhs, absRhs);
			return negative(subtract(absRhs, lhs));
		}
		else // lhs & rhs are both +ve
		{
			tempLhs = lhs;
			tempRhs = rhs;
		}
	}

	string result = easyAdd(tempLhs, tempRhs);
	if (makeNegative)
		return negative(result);
	return result;

}
string Math::easySubtract(const string& lhs, const string& rhs)
{
	// easy because both lhs & rhs are +ve *** and *** the lhs > rhs

	string tlhs = lhs; // need to modify for borrowing

	int n = tlhs.length();
	int m = rhs.length();

	try
	{
		if (n < 1)
			throw invalid_argument("lhs is the empty string");
		if (m < 1)
			throw invalid_argument("rhs is the empty string");

		int i = n - 1;
		int j = m - 1;
		int k;
		char ic;
		char jc;
		string result = "";

		while (i >= 0)
		{
			ic = tlhs[i];
			if (ic < '0' || ic > '9')
				throw invalid_argument("lhs contains at least one not in [0,1, 2, ..., 9]");
			jc = (j >= 0) ? (rhs[j]) : '0';
			if (jc <'0' || jc>'9')
				throw invalid_argument("rhs contains at least one not in [0,1, 2, ..., 9]");

			if (ic >= jc)
			{
				result = ((char)(((int)ic - (int)jc) + (int)'0')) + result;
			}
			else // borrow (assume rhs > lhs)
			{
				k = i - 1;
				while (tlhs[k] == '0')
					k--;
				tlhs[k] -= 1; // borrow
				for (k = k + 1; k < i; k++) // replace 0s with 9s
					tlhs[k] = '9';
				result = ((char)(((int)(ic + 10) - (int)jc) + (int)'0')) + result;
			}
			i--;
			j--;
		}
		return trim(result);
	}
	catch (...)
	{
		throw;
	}
}
string Math::subtract(const string& lhs, const string& rhs)
{
	string tempLhs;
	string tempRhs;
	bool makeNegative = false;

	if (isNegative(lhs))
	{
		if (isNegative(rhs)) // lhs & rhs are both -ve
		{
			string absLhs = abs(lhs);
			string absRhs = abs(rhs);
			if (isGreaterThan(absRhs, absLhs)) // abs( rhs ) > abs( lhs ).  swap lhs & rhs.  do subtraction.  example:  -2 - -5 = abs( 5 ) - abs( 2 ) = 3
			{
				tempLhs = absRhs;
				tempRhs = absLhs;
			}
			else // do subtraction.  reverse sign.  example:  -5 - -3 = -(5 - 3) = -2
			{
				tempLhs = absLhs;
				tempRhs = absRhs;
				makeNegative = true;
			}
		}
		else // lhs is -ve.  rhs is +ve.  do addition with abs( lhs ) and rhs.  reverse sign.  example:  -2 - 5 = -( 2 + 5 ) = 7; -5 - -2 = -( 5 + 2 ) = -7
		{
			return negative(add(abs(lhs), rhs));
		}
	}
	else
	{
		if (isNegative(rhs)) // lhs is +ve.  rhs is -ve.  do addition lhs and abs( rhs ).  example:  5 - -2 = 5 + 2 = 7;  2 - -5 = 2 + 5 = 7

		{
			return add(lhs, abs(rhs));
		}
		else // lhs & rhs are both +ve
		{
			if (isGreaterThan(lhs, rhs)) // easy
			{
				tempLhs = lhs;
				tempRhs = rhs;
			}
			else // swap lhs & rhs, make result -ve
			{
				tempLhs = rhs;
				tempRhs = lhs;
				makeNegative = true;
			}
		}
	}

	string result = easySubtract(tempLhs, tempRhs);
	if (makeNegative)
		return negative(result);
	return result;
}
string Math::easyMultiply(const string& lhs, const string& rhs)
{
	try
	{
		int n = lhs.length();
		int m = rhs.length();

		if (n < 1)
			throw invalid_argument("lhs is the empty string");
		if (m < 1)
			throw invalid_argument("rhs is the empty string");

		int carry;
		int i, j, p;
		char jc, ic;
		string result;
		Queue<string> results;
		for (j = m - 1; j >= 0; j--)
		{
			result = "";
			carry = 0;
			for (int k = j; k < m - 1; k++)
				result = "0" + result;
			jc = rhs[j];
			if (jc <'0' || jc>'9')
				throw invalid_argument("rhs contains at least one not in [0,1, 2, ..., 9]");
			for (i = n - 1; i >= 0; i--)
			{
				ic = lhs[i];
				if (i == n - 1 && (ic < '0' || ic > '9'))
					throw invalid_argument("lhs contains at least one not in [0,1, 2, ..., 9]");
				p = ((jc - (int)'0')*(ic - (int)'0')) + carry;
				if (p >= 10)
				{
					result = (char)((p % 10) + (int)'0') + result;
					carry = (p / 10);
				}
				else
				{
					result = (char)(p + (int)'0') + result;
					carry = 0;
				}
			}
			if (carry > 0)
				result = (char)(carry + (int)'0') + result;
			results.enqueue(result);
		}

		result = results.dequeue();
		while (!results.isEmpty())
			result = easyAdd(result, results.dequeue());
		return trim(result);
	}
	catch (...)
	{
		throw;
	}
}
string Math::multiply(const string& lhs, const string& rhs)
{
	try
	{
		string lhsAbs = abs(lhs);
		string rhsAbs = abs(rhs);
		string result;
		bool makeNegative;
		if (isNegative(lhs))
		{
			if (isNegative(rhs))
				makeNegative = false;
			else
				makeNegative = true;
		}
		else
		{
			if (isNegative(rhs))
				makeNegative = true;
			else
				makeNegative = false;
		}


		result = easyMultiply(lhsAbs, rhsAbs);
		if (makeNegative)
			return negative(result);
		return result;
	}
	catch (...)
	{
		throw;
	}
}
string Math::easyDivide(const string& lhs, const string& rhs)
{
	string divisor = trim(rhs);
	string dividend = trim(lhs);
	string quotient = "";

	int divisorLen = divisor.length();
	int dividendLen = dividend.length();

	try
	{
		if (dividendLen < 1)
			throw invalid_argument("dividend is the empty string");
		if (divisorLen < 1)
			throw invalid_argument("divisor is the empty string");
		if (isZero(divisor))
			throw DivideByZeroException();
		if (isNegative(divisor))
			throw invalid_argument("divisor is negative");
		if (isNegative(dividend))
			throw invalid_argument("dividend is negative");
		if (isGreaterThan(divisor, dividend))
			return "0";

		int dividendPos;
		string partialDividend = dividend.substr(0, divisorLen);
		if (isGreaterThan(divisor, partialDividend))
		{
			partialDividend = dividend.substr(0, divisorLen + 1);
			dividendPos = divisorLen;
		}
		else
		{
			dividendPos = divisorLen - 1;
		}

		string partialQuotient;
		string product;
		while (dividendPos < dividendLen)
		{
			partialDividend = trim(partialDividend);
			// this is very inefficient
			partialQuotient = "1";
			product = easyMultiply(divisor, partialQuotient);
			while (isGreaterThanOrEqual(partialDividend, product))
			{
				partialQuotient = easyAdd(partialQuotient, "1");
				product = easyMultiply(divisor, partialQuotient);
			}
			partialQuotient = easySubtract(partialQuotient, "1");
			product = easyMultiply(divisor, partialQuotient);

			quotient += partialQuotient;
			partialDividend = easySubtract(partialDividend, product);
			dividendPos++;

			if (dividendPos < dividendLen)
			{
				partialDividend += dividend[dividendPos];
				while (isGreaterThan(divisor, partialDividend) && dividendPos < dividendLen)
				{
					quotient += '0';
					dividendPos++;
					if (dividendPos < dividendLen)
						partialDividend += dividend[dividendPos];
				}
			}
		}

		return quotient;
	}
	catch (...)
	{
		throw;
	}
}
string Math::divide(const string& lhs, const string& rhs)
{
	try
	{
		string lhsAbs = abs(lhs);
		string rhsAbs = abs(rhs);
		string result;
		bool makeNegative;
		if (isNegative(lhs))
		{
			if (isNegative(rhs))
				makeNegative = false;
			else
				makeNegative = true;
		}
		else
		{
			if (isNegative(rhs))
				makeNegative = true;
			else
				makeNegative = false;
		}

		result = easyDivide(lhsAbs, rhsAbs);
		if (makeNegative)
			return negative(result);
		return result;
	}
	catch (...)
	{
		throw;
	}
}