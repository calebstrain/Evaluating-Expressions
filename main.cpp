// @author Caleb Strain 

#include <iostream>
#include "Stack.h"
#include "Token.h"
#include "Queue.h"
#include "Math.h"
#include "StackEmptyException.h"
#include "QueueEmptyException.h"
#include "BigInteger.h"
#include "ArgumentManager.h"
#include "DivideByZeroException.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

bool isUnary(int i, bool foundToken, Token& lastToken)
{
	if (i == 0)
		return true;
	if (!foundToken)
		return false;
	Token::Type t = lastToken.getType();
	switch (t)
	{
	case Token::Type::plus:
		throw invalid_argument("not a valid infix expression"); // NO DOUBLE OPERATORS!
	case Token::Type::minus:
		throw invalid_argument("not a valid infix expression"); 
	case Token::Type::multiply:
		throw invalid_argument("not a valid infix expression");
	case Token::Type::divide:
		throw invalid_argument("not a valid infix expression");
	case Token::Type::left:
		return true;
	}
	return false;
}

void stringToInfix(const string& s, Queue<Token>& infix)
{
	int len = s.length();

	if (len < 1)
		return;
	int i = 0;
	int c;
	int state = 0;
	string literal;
	bool foundToken = false;
	Token lastToken;
	int addRightToLiteral = 0;

	try
	{
		while (true)
		{
			c = s[i];
			switch (state)
			{
			case 0:
				if (c == '+') // need to know if this is a unary + or a binary +
				{
					if (isUnary(i, foundToken, lastToken))
					{
						state = 0;
						foundToken = true;
						lastToken = Token(Token::Type::plus);
					}
					else
					{
						foundToken = true;
						lastToken = Token(Token::Type::plus);
						infix.enqueue(lastToken);
						state = 0;
					}
				}
				else if (c == '-') // need to know if this is a unary - or a binary -
				{
					if (isUnary(i, foundToken, lastToken))
					{
						infix.enqueue(Token("0"));
						foundToken = true;
						lastToken = Token(Token::Type::minus);
						infix.enqueue(lastToken);
					}
					else
					{

						foundToken = true;
						lastToken = Token(Token::Type::minus);
						infix.enqueue(lastToken);
						state = 0;
					}
				}
				else if (c == '*')
				{
					if (!isUnary(i, foundToken, lastToken)) 
					{
						foundToken = true;
						lastToken = Token(Token::Type::multiply);
						infix.enqueue(lastToken);
						state = 0;
					}
				}
				else if (c == '/')
				{
					if (!isUnary(i, foundToken, lastToken))
					{
						foundToken = true;
						lastToken = Token(Token::Type::multiply);
						infix.enqueue(lastToken);
						state = 0;
					}
				}
				else if (c == '(')
				{
					foundToken = true;
					lastToken = Token(Token::Type::left);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == ')')
				{
					foundToken = true;
					lastToken = Token(Token::Type::right);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c >= '0' && c <= '9')
				{
					literal = "";
					literal += c;
					state = 1;
				}
				else if( c != ' ' )
				{
					throw invalid_argument("not a valid infix expression");
				}
				break;
			case 1:
				if (c >= '0' && c <= '9')
				{
					literal += c;
					state = 1;
				}
				else if (c == '+')
				{
					infix.enqueue(Token(literal));
					if (addRightToLiteral)
					{
						for (int j = 0; j < addRightToLiteral; j++)
							infix.enqueue(Token(Token::Type::right));
						addRightToLiteral = 0;
					}
					foundToken = true;
					lastToken = Token(Token::Type::plus);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == '-')
				{
					infix.enqueue(Token(literal));
					if (addRightToLiteral)
					{
						for (int j = 0; j < addRightToLiteral; j++)
							infix.enqueue(Token(Token::Type::right));
						addRightToLiteral = 0;
					}
					foundToken = true;
					lastToken = Token(Token::Type::minus);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == '*')
				{
					infix.enqueue(Token(literal));
					foundToken = true;
					lastToken = Token(Token::Type::multiply);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == '/')
				{
					infix.enqueue(Token(literal));
					foundToken = true;
					lastToken = Token(Token::Type::divide);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == '(')
				{
					infix.enqueue(Token(literal));
					if (addRightToLiteral)
					{
						for (int j = 0; j < addRightToLiteral; j++)
							infix.enqueue(Token(Token::Type::right));
						addRightToLiteral = 0;
					}
					foundToken = true;
					lastToken = Token(Token::Type::left);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if (c == ')')
				{
					infix.enqueue(Token(literal));
					if (addRightToLiteral)
					{
						for (int j = 0; j < addRightToLiteral; j++)
							infix.enqueue(Token(Token::Type::right));
						addRightToLiteral = 0;
					}
					foundToken = true;
					lastToken = Token(Token::Type::right);
					infix.enqueue(lastToken);
					state = 0;
				}
				else if( c != ' ' )
				{
					throw invalid_argument("not a valid infix expression");
				}
			}
			i++;
			if (i >= len)
			{
				if (state == 1)
				{
					infix.enqueue(Token(literal));
					if (addRightToLiteral)
					{
						for (int j = 0; j < addRightToLiteral; j++)
							infix.enqueue(Token(Token::Type::right));
					}
				}
				return;
			}
		}
	}
	catch (...)
	{
		throw;
	}
}

string evaluatePostFix(Queue<Token>& q)
{
	Token t;
	Stack<string> s;
	string lhs;
	string rhs;
	try
	{
		while (!q.isEmpty())
		{
			t = q.dequeue();
			if (t.getType() == Token::Type::literal)
			{
				s.push(t.getValue());
			}
			else
			{
				rhs = s.pop();
				lhs = s.pop();
				switch (t.getType())
				{
				case Token::Type::plus:
					s.push(Math::add(lhs, rhs));
					break;
				case Token::Type::minus:
					s.push(Math::subtract(lhs, rhs));
					break;
				case Token::Type::multiply:
					s.push(Math::multiply(lhs, rhs));
					break;
				case Token::Type::divide:
					if (rhs == "0")
						throw DivideByZeroException();
					s.push(Math::divide(lhs, rhs));
					break;
				default:
					throw invalid_argument("invalid post fix expression");
				}
			}
		}
		return s.pop();
	}
	catch (...)
	{
		throw;
	}
}

// https://en.wikipedia.org/wiki/Shunting-yard_algorithm

void infixToPostfix(Queue<Token>& infix, Queue<Token>& postfix)
{
	try
	{
		Token token;
		Stack<Token> operators;
		while (!infix.isEmpty())
		{
			token = infix.dequeue();
			switch (token.getType())
			{
			case Token::Type::literal:
				postfix.enqueue(token);
				break;
			case Token::Type::left:
				operators.push(token);
				break;
			case Token::Type::right:
				while (operators.top().getType() != Token::Type::left)
					postfix.enqueue(operators.pop());
				operators.pop();
				break;
			default: // plus, minus, multiply or divide
				while (!operators.isEmpty() && Token::hasPrecedence(operators.top(), token))
					postfix.enqueue(operators.pop());
				operators.push(token);
				break;
			}
		}
		while (!operators.isEmpty())
			postfix.enqueue(operators.pop());
	}
	catch (...)
	{
		throw;
	}
}

void evaluate(const string& expression, string& result, bool& exceptionThrown)
{
	Queue<Token> infix;
	Queue<Token> postfix;

	try
	{
		stringToInfix(expression, infix);
		infixToPostfix(infix, postfix);
		result = evaluatePostFix(postfix);
		exceptionThrown = false;
	}
	catch (...)
	{
		exceptionThrown = true;
	}
}

bool isEmpty(ifstream& f)
{
	return f.peek() == ifstream::traits_type::eof();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: .calculate input=input31.txt output=output31.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);

	string actualResultValue; // change to string
	bool exceptionThrown;

	ifstream f( am.get("input") );
	ofstream ofs( am.get("output") );
	if (isEmpty(f)) { return 0; }

	string line;
	vector<string> lines;
	while (!f.eof())
	{
		getline(f, line);
		if (!line.empty())
		{
			lines.push_back(line);
		}
	}

	string* results = new string[lines.size()];
	bool errorExists = false;
	for (int i = 0; i < lines.size(); i++)
	{
		evaluate(lines[i], actualResultValue, exceptionThrown);
		if (exceptionThrown == true)
		{
			ofs << "error" << endl;
		}
		else 
		{
			if (i < (lines.size() - 1))
				ofs << lines[i] << "=" << actualResultValue << endl;
			else
				ofs << lines[i] << "=" << actualResultValue;
		}
	}
	
	delete[] results;
	
	return 0;
}
