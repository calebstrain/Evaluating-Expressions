#include "BigInteger.h"

string BigInteger::validate(const string& s)
{
	int len = s.length();
	if (len < 1)
		throw invalid_argument("empty string");
	string result = "";
	int state = 0;
	int i = 0;
	char c;
	while (true)
	{
		c = s[i];
		switch (state)
		{
		case 0:
			if (c == ' ' || c == '\t')
			{
				state = 0;
			}
			else if (c == '-')
			{
				result += '-';
				state = 1;
			}
			else if (c == '0')
			{
				state = 2;
			}
			else if (c >= '1' && c <= '9')
			{
				result += c;
				state = 3;
			}
			else
			{
				throw invalid_argument("not a number");
			}
			break;
		case 1:
			if (c == '0')
			{
				state = 2;
			}
			else if (c >= '1' && c <= '9')
			{
				result += c;
				state = 3;
			}
			else
			{
				throw invalid_argument("not a number");
			}
			break;
		case 2:
			if (c == '0')
			{
				state = 2;
			}
			else if (c >= '1' && c <= '9')
			{
				result += c;
				state = 3;
			}
			else
			{
				throw invalid_argument("not a number");
			}
			break;
		case 3:
			if (c == ' ' || c == '\t')
			{
				state = 4;
			}
			else if (c >= '0' && c <= '9')
			{
				result += c;
				state = 3;
			}
			else
			{
				throw invalid_argument("not a number");
			}
			break;
		case 4:
			if (c == ' ' || c == '\t')
			{
				state = 4;
			}
			else
			{
				throw invalid_argument("not a number");
			}
			break;
		}
		i++;
		if (i >= len)
		{
			if (result == "")
			{
				result = "0";
				return result;
			}
			else if (result == "-")
			{
				throw invalid_argument("not a number");
			}
			return result;
		}
	}
}

BigInteger::BigInteger(const string& s)
{
	try
	{
		value = validate(s);
	}
	catch (...)
	{
		throw;
	}
}
BigInteger::BigInteger(const BigInteger& n)
{
	this->value = (const char*)n;
}

BigInteger::operator const char*() const
{
	return value.c_str();
}

BigInteger BigInteger::operator+(const BigInteger& rhs) const
{
	try
	{
		int i = value.length() - 1;
		string right = (const char*)rhs;
		int j = right.length() - 1;

		string result = "";
		char ic;
		char jc;
		int n;
		int carry = 0;
		while (i >= 0 || j >= 0)
		{
			ic = (i >= 0) ? (value[i]) : ('0');
			jc = (j >= 0) ? (right[j]) : ('0');

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
		return BigInteger(result);
	}
	catch (...)
	{
		throw;
	}
}


