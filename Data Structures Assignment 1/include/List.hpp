
#ifndef LIST_HPP
#define LIST_HPP

#include "Node.hpp"

class List {

public:


	List();
	~List();
	List(Node* myNode);

	void Add(int value);
	//void insert(int index, int data);
	void Remove();
	void RemoveAt(int Index);
	void Clear();
	void Print();

	bool IsEmpty();
	Node* FindPreviousByPosition(int Index);
	int Size();
	double GetAvgOfList();

private:
	friend class YoneticiList;
	friend class UIx;


	Node* head;
	int length;
	Node* getAddr();

	
};



#endif //LIST_HPP