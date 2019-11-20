#ifndef __STACK_H__
#define __STACK_H__

#include "StackEmptyException.h"
#include "Math.h"

template<class T>
class Stack
{
private:
	class Node
	{
	public:
		T item;
		Node* next;
		Node(T item, Node* next)
		{
			this->item = item;
			this->next = next;
		}
	};
	Node* head;
public:
	Stack()
	{
		head = NULL;
	}
	~Stack()
	{
		Node* i = head;
		Node* t;
		while (i != NULL)
		{
			t = i->next;
			delete i;
			i = t;
		}
	}
	void push(T item)
	{
		head = new Node(item, head);
	}
	T pop()
	{
		if (head == NULL) throw StackEmptyException();
		T item = head->item;
		Node* temp = head->next;
		delete head;
		head = temp;
		return item;
	}
	T top()
	{
		if (head == NULL) throw StackEmptyException();
		return head->item;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
};

#endif
