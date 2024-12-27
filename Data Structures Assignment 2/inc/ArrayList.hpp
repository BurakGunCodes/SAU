#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP


#include <cmath>

class ArrayList{
	private:
		int *items;
		int length;
		int capacity;
		void Reserve(int newCapacity);
	public:
		ArrayList();
		int Size() ;
		bool IsEmpty() ;
		int ElementAt(int i) ;
		void ChangeAt(int index, int value) ;
		void Remove( int item) ;
		void RemoveAt(int i) ;
		void Add( int item);
		void Clear();
		
		~ArrayList();
};

#endif
