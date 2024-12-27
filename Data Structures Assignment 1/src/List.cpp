/** 
* @file List.cpp
* @description Cift Yonlu Bagli Liste icin temel fonksiyonlarý kapsar
* @course 2.Ogretim A Grubu
* @assignment Odev_1
* @date 24/11/2022
* @author Burak Gun, burak.gun1@ogr.sakarya.edu.tr
*/

#include <iostream>
#include <iomanip>
#include "List.hpp"
#include "Node.hpp"
#include "YoneticiList.hpp"

using namespace std;

List::List()
{
	head = new Node();
	length = 0;
	//cout << this <<" adresinde linked list olusturuldu." << endl;
}

List::List(Node* myNode)
{
	head = myNode;
	length = 0;
	//cout << this << " adresinde linked list olusturuldu." << endl;
}

List::~List()
{
	Clear();
	delete head;
	//cout << this << " adresindeki linked list silindi " << endl;
}

void List::Add(int value)
{

	Node* node = new Node(value);

	if (head->next == nullptr)
	{
		head->next = node;
		node->prev = head;

	}
	else
	{
		Node* iter = head;
		while (iter->next != nullptr)
		{
			iter = iter->next;
		}
		iter->next = node;
		node->next = nullptr;
		node->prev = iter;

	}
	length++;
}


//void List::insert(int index, int data)
//{
//	if (index == 0 || index > length) throw "Out of Range";
//
//	Node* node = new Node(data);
//	Node* temp;
//	Node* iter = findPreviousByPosition(index);
//
//
//	node->next = iter->next;
//	iter->next->prev = node;
//	node->prev = iter;
//	iter->next = node;
//	length++;
//
//}

// head index 0 olarak tasarlandý.
Node* List::FindPreviousByPosition(int index)
{
	if (index > length+1)throw "Out of Range";

	Node* iter = head;
	

	for (int i = 1; i < index ; i++)
	{
		if (iter != nullptr)
		{
			iter = iter->next;
		}
		
	}
	return iter;
}

// son elemaný siler.
void List::Remove()
{

	Node* iter = FindPreviousByPosition(length);
	Node* temp = iter->next;

	iter->next = 0;

	delete temp;

	length--;
}

//istenilen indexte bulunan elemaný siler
void List::RemoveAt(int index)
{

	if(index <0 || index > length)throw "Index Out of Range";	

	Node* iter;
	Node* temp;
	Node* toBeDeleted;

	// ilk durum olmasý þartý
	if(length == 1 && index == 1)
	{
		iter = head;
		toBeDeleted = iter->next;

		iter->next = 0;
		delete toBeDeleted;
		length--;

	}
	else if (index == length)
	{
		// length içeride çaðrýlýyor
		Remove();
		
	}
	else
	{
		iter = FindPreviousByPosition(index);
		toBeDeleted = iter->next;
		temp = toBeDeleted->next;


		iter->next = temp;
		temp->prev = iter;

		delete toBeDeleted;
		length--;
	}
	
}


	




void List::Clear()
{
	while (!IsEmpty())
	{
		Remove();
	}
}

bool List::IsEmpty()
{
	return length == 0;
}


int List::Size()
{
	return this->length;
}


void List::Print()
{
	Node* iter = head;

	for (int i = 0; i < length + 1; i++)// head dahil olmadan length hesapþan
	{
		std::cout << "length: " << length << " data : " << iter->avg << std::endl;
		iter = iter->next;


	}

}




Node* List::getAddr()
{
	return head;
}


double List::GetAvgOfList()
{
	Node* iter = head;

	double sum = 0;

	while (iter != 0)
	{
		sum = sum + iter->data;
		iter = iter->next;
	}
	return (sum / length);
}