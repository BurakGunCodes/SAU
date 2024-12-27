/** 
* @file Node.cpp
* @description Listenin her bir elemanini temsil eden dugum sinifidir.
* @course 2.Ogretim A Grubu
* @assignment Odev_1
* @date 24/11/2022
* @author Burak Gun, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Node.hpp"
#include <iostream>
#include "List.hpp"

#define nullptr 0;

using namespace std;


Node::Node()
{
	this->avg = 0;
	this->data = 0;
	this->prev = 0;
	this->next = 0;
	this->addr = 0;
	//std::cout  << " " << this << " adresinde node olustu" << " value: " << this->data << endl;
}

Node::Node(int data)
{
	this->data = data;
	this->prev = 0;
	this->next = 0;
	this->addr = 0;
	this->avg = 0;
	//std::cout  << " " << this << " adresinde node olustu" << " value: " << this->data << endl;
}

Node::Node(Node* addr)
{
	this->data = data;
	this->prev = 0;
	this->next = 0;
	this->addr = addr;
	this->avg = 0;
	//std::cout  << " " << this << " adresinde node olustu" << " value: " << this->data << endl;
}

Node::Node(Node* addr, double avg)
{
	this->data = data;
	this->prev = 0;
	this->next = 0;
	this->addr = addr;
	this->avg = avg;
	//std::cout << " " << this << " adresinde node olustu" << " avg value: " << this->avg << endl;
}


Node::~Node()
{

	//std::cout <<  this << " adresindeki node silindi" << " value: " << this->data << endl;
	this->avg = 0;
	this->data = 0;
	this->prev = 0;
	this->next = 0;
	this->addr = 0;
}

