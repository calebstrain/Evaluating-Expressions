#include <sstream>
#include "Token.h"
#include "DivideByZeroException.h"
#include <stdexcept>

using namespace std;

Token::Token()
{
	type = Token::Type::literal;
	value = "0";
}

Token::Token(Type type)
{
	this->type = type;
	value = "0";
}

//Token::Token(string value)
//{
//	type = Token::Type::literal;
//	this->value = value;
//}

Token::Token(const char* s)
{
	try
	{
		type = Token::Type::literal;
		value = s;
	}
	catch (...)
	{
		throw;
	}
}

Token::Token(const string& s)
{
	try
	{
		type = Token::Type::literal;
		value = s;
	}
	catch (...)
	{
		throw;
	}
}

Token::Type Token::getType() const
{
	return type;
}

string Token::getValue() const
{
	return value;
}

void Token::set(Type type)
{
	this->type = type;
	if (type == Token::Type::literal)
		value = "0";
}

void Token::setLiteralValue(const char* s)
{
	try
	{
		value = s;
		type = Token::Type::literal;
	}
	catch (...)
	{
		throw;
	}
}

void Token::setLiteralValue(const string& s)
{
	try
	{
		value = s;
		type = Token::Type::literal;
	}
	catch (...)
	{
		throw;
	}
}

Token& Token::operator=(const Token& rhs)
{
	if (&rhs == this)
		return *this;
	this->type = rhs.getType();
	this->value = rhs.getValue();
	return *this;
}

bool Token::hasPrecedence(const Token& op0, const Token& op1)
{
	switch (op0.getType())
	{
	case Token::Type::plus:
	case Token::Type::minus:
		switch (op1.getType())
		{
		case Token::Type::multiply:
		case Token::Type::divide:
			return false;
		default:
			return true;
		}
		break;
	case Token::Type::left:
	case Token::Type::right:
		return false;
	default:
		return true;
	}
}

