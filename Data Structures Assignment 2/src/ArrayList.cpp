/**
* @file ArrayList.cpp
* @description Doku s�n�f� bu s�n�ftan kal�t�m almaktad�r. Dokular i�erisinde ka� adet h�cre tutulaca�� belli olmad��� ve mutasyon s�ras�nda
	h�crelerdeki indekslere s�rekli olarak gidilece�i i�in ArrayList tercih edilmi�tir. LinkedList ile bu i�lemler �ok daha maliyetli olacakt�r.
* @course 2.��retim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak G�n, burak.gun1@ogr.sakarya.edu.tr
*/

#include "ArrayList.hpp"
#include <iostream>
using namespace std;

void ArrayList::Reserve(int newCapacity)
{
	if(capacity>=newCapacity) return;
	int *tmp = new int[newCapacity];
	for(int j=0;j<length;j++) tmp[j]= items[j];
	if(items != 0) delete [] items;
	items = tmp;
	capacity = newCapacity;
}

ArrayList::ArrayList()
{
	length = 0;
	capacity=1;
	items = new int[capacity];
}


int ArrayList::Size() 
{
	return length;
}

bool ArrayList::IsEmpty() 
{
	return Size() == 0;
}

int ArrayList::ElementAt(int i) 
{
	//if(i<0 || i>=length) 
	return items[i]; 
}

void ArrayList::ChangeAt(int index, int value) 
{
	items[index] = value;
}

void ArrayList::Remove( int item) 
{
	for(int i=0;i<length;i++)
	{
		if(items[i] == item)
		{
			RemoveAt(i);
			return;
		}
	}
			
}

void ArrayList::RemoveAt(int i)
{
	if(i<0 || i>=length) 
	for(int j=i+1;j<length;j++) items[j - 1] = items[j];
		length--;
}

void ArrayList::Add( int item)
{	
			
	if(length >= capacity) Reserve(2*capacity); 
	items[length] = item;
	length++;
}


void ArrayList::Clear()
{
	length = 0;
}

ArrayList::~ArrayList()
{
	if(items != 0) delete [] items;
}

