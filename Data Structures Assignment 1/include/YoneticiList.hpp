
#ifndef YONETICILIST_HPP
#define YONETICILIST_HPP

#include <iomanip>
#include "List.hpp"

class YoneticiList : public List
{

 public:

	 friend class UIx;

	YoneticiList();
	~YoneticiList();

	void AddByAvg(List* list, double Average);
	void PrintList(List* Addr);

	void CopyAndAddList(YoneticiList* yonetici);
	void RandomDelete(YoneticiList* yonetici, int index);
	Node* GoToSatir(YoneticiList* yonetici);
	bool IsSatirEmpty(YoneticiList* yonetici);
	void RemoveSatir(YoneticiList* yonetici);
	void RemoveSatirNodeAt(YoneticiList* yonetici, int index);
	int SizeOfNode(YoneticiList* yonetici);
	void RemoveYoneticiNodeAt();
	 

	//void print();
	//int size();
	//using List::print;
	//friend int List::size();

	
 private:

	 
};



#endif //YONETICILIST_HPP