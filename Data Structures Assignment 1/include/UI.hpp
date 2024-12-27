

#ifndef UI_HPP
#define UI_HPP


#include <iostream>
#include <windows.h>
#include "Node.hpp"
#include "List.hpp"
#include "YoneticiList.hpp"

void SetCursorPosition(char x, char y);


class UIx {

public:
		void UI_Header();
		void UI_Yonetici(YoneticiList* yonetici);
		void UI_Satir(YoneticiList* yonetici);
		void UI_Selector(int Index);
		Node* goToSatir2(YoneticiList* yonetici);
		Node* moveYoneticiIterByPageNumber(YoneticiList* yonetici);
		
private:
	


};

#endif // UI_HPP


//void UI_Satir(int CurrentIndex, DoublyNode* Addr);
//void UI_Selector(int CurrentIndex);
