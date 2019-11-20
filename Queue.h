#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "QueueEmptyException.h"

template<class T>
class Queue
{
private:
	class Node
	{
	public:
		T item;
		Node* next;
		Node(T item)
		{
			this->item = item;
			next = NULL;
		}
	};
	Node* head;
	Node* tail;
public:
	Queue()
	{
		head = NULL;
		tail = NULL;
	}
	~Queue()
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
	void enqueue(T item)
	{
		Node* n = new Node(item);
		if (head == NULL)
			head = n;
		else
			tail->next = n;
		tail = n;
	}
	T dequeue()
	{
		if (head == NULL) throw QueueEmptyException();
		T item = head->item;
		Node* temp = head->next;
		delete head;
		head = temp;
		if (head == NULL)
			tail = NULL;
		return item;
	}
	bool isEmpty()
	{
		return (head == NULL);
	}
};

#endif