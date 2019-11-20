#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
using namespace std;

class Token
{
public:
	enum Type { plus, minus, multiply, divide, left, right, literal, unaryMinus };
private:
	Type type;
	string value;
public:
	Token();
	Token(Type type);
	//Token(string value);
	Token(const char* s);
	Token(const string& s);
	Token::Type getType() const;
	string getValue() const;
	void set(Type type);
	void setLiteralValue(const char* s);
	void setLiteralValue(const string& s);
	//string toString() const;
	Token& operator=(const Token& rhs);
	//static long long evaluate(const Token& lhs, const Token& op, const Token& rhs);
	static bool hasPrecedence(const Token& op0, const Token& op1);  // returns true if op0 has same/higher precendence as op1
};

#endif



