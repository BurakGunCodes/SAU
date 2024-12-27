/**
* @file Queue.cpp
* @description Her satirda bulunan degerleri Radix Sort ile sýralamýmýzý saðlayan kuyruk sýnýfýdýr. Siralama icin kullanýldý.
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Queue.hpp"


QNode* Queue::previousMaxNode() 
{
	QNode* prev = NULL;
	QNode* tmp = front;

	int max = front->item;
	while (tmp->next != NULL) 
	{
		if (tmp->next->item > max) 
		{
			max = tmp->next->item;
			prev = tmp;
		}
		tmp = tmp->next;
	}
	return prev;
}


Queue::Queue()
{
	front = back = NULL;
	length = 0;
}


int Queue::count()const 
{
	return length;
}


bool Queue::isEmpty()const
{
	return length == 0;
}


void Queue::enqueue(const int item)
{
	QNode* last = new QNode(item);
	if (isEmpty()) front = back = last;
	else 
	{
		back->next = last;
		back = back->next;
	}
	length++;
}


void Queue::dequeue()
{
	if (isEmpty()) throw "Queue is Empty";

	QNode* tmp = front;

	front = front->next;

	delete tmp;

	length--;
}


void Queue::dequeueMax()
{
	if (isEmpty()) throw "Queue is Empty";

	QNode* prev = previousMaxNode();
	QNode* tmp;

	if (prev == NULL) dequeue();
	else 
	{
		if (prev->next == back) back = prev;
		tmp = prev->next;
		prev->next = prev->next->next;
		delete tmp;
		length--;
	}
}

	
void Queue::clear() 
{
	while (!isEmpty())dequeue();
}


int Queue::peek()const 
{
	if (isEmpty()) throw "Queue is Empty";
	return front->item;
}


int Queue::peekMax() 
{
	if (isEmpty()) throw "Queue is Empty";

	QNode* prev = previousMaxNode();

	if (prev == NULL) return peek();
	return prev->next->item;
}


Queue::~Queue() 
{
	clear();
}