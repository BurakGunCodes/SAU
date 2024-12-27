#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
using namespace std;


class QNode
{
	public:
		int item;
		QNode *next;
		
		QNode(int item, QNode *next=NULL)
		{
			this->item = item;
			this->next = next;
		}
};


class Queue {
private:
	QNode* front;
	QNode* back;
	int length;

	QNode* previousMaxNode();

public:
	Queue();
	int count()const;
	bool isEmpty()const;
	void enqueue(const int item);
	void dequeue();

	void dequeueMax();
	void clear();
	int peek()const;
	int peekMax();
	~Queue();
};

#endif
