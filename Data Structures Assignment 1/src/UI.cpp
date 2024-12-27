/** 
* @file UI.cpp
* @description Ekranda gorunecek olan her bilginin duzenlendigi siniftir.
	Sayfa gostergeci(header), yonetici listesinde bulunan dugumleri yazdirir, her bir dugumun adres gösterdigi satir listesini yazdirir.
	UI_Selector ise rasgele silinme islemi yapılacagi zaman, hangi verinin silinecegini ok ile gösterir.
* @course 2.Ogretim A Grubu
* @assignment Odev_1
* @date 24/11/2022
* @author Burak Gun, burak.gun1@ogr.sakarya.edu.tr
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

#include "UI.hpp"
#include "Node.hpp"
#include "List.hpp"

#include "YoneticiList.hpp"

using namespace std;

extern int verilerSatirSayisi;
extern int iterCurrentIndex;

static int TotalPageNumber = 0;
static int CurrentPageNumber = 0;

static int row = 18;
static int x = 0;
static int col = 2;
static int lastState = 0;


void SetCursorPosition(char x, char y);


// Sayfanın en ustunde bulunan onceki/sonraki ve ilgili sayfa numarasını gosteren kisimdir.
// Her sayfada 8 dizi elemanı olacak sekilde yapıldi
// Veriler dosyasindaki satir sayisinin mod(%8)una ve silinen dugumlere gore sayfa sayisi degismektedir.
void UIx::UI_Header()
{
	CurrentPageNumber = 0;
	TotalPageNumber = 0;


	if (verilerSatirSayisi <= 8) {
		TotalPageNumber = 1;
	}
	else if (verilerSatirSayisi % 8 == 0) {
		TotalPageNumber = verilerSatirSayisi / 8;
	}
	else {
		TotalPageNumber = (verilerSatirSayisi / 8) + 1;;
	}

	if (iterCurrentIndex <= 8) {
		CurrentPageNumber = 1;
	}
	else if (iterCurrentIndex % 8 == 0) {
		CurrentPageNumber = iterCurrentIndex / 8;
	}
	else {
		CurrentPageNumber = (iterCurrentIndex / 8) + 1;;
	}

	//sayfa 1/4    sonraki-->
	string pageIndexFirst;
	string pageIndexLast;

	if (CurrentPageNumber == 1) {
		pageIndexFirst = "ilk";
	}
	else {
		pageIndexFirst = "<--onceki";
	}

	if (CurrentPageNumber == TotalPageNumber) {
		pageIndexLast = "son";
	}
	else {
		pageIndexLast = "sonraki-->";
	}

	cout << pageIndexFirst << setw(120) << "(" << CurrentPageNumber << "/" << TotalPageNumber << ")" << pageIndexLast << endl;
}




void UIx::UI_Yonetici(YoneticiList* yonetici) 
{

	int yoneticiSatir = 2;
	int yoneticiSatirAralik;
	int yoneticiSutun = 18;
	int yoneticiSutunAralik = 0;


	Node* iter = moveYoneticiIterByPageNumber(yonetici);

	for (int k = 0; k < 8;  k++) {
		if (iter == 0)break;// eğer ilk yada son sayfada 8 değişken yok ise, çıkış yap.
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 0); cout << setw(14) << iter << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 1); cout << "---------------" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 2); cout << "|" << setw(14) << iter->prev << "|" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 3); cout << "---------------" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 4); cout << "|" << setw(14) << iter->avg << "|" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 5); cout << "---------------" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 6); cout << "|" << setw(14) << iter->next << "|" << endl;
		SetCursorPosition(yoneticiSutun * yoneticiSutunAralik, yoneticiSatir + 7); cout << "---------------" << endl;

		yoneticiSutunAralik++;// satir degeri saga dogru artacak

		iter = iter->next;

		cout << "Index Numarasi: " << iterCurrentIndex << "," << " Veri Sayisi: " << verilerSatirSayisi<< endl;
		
	} 
}




Node* UIx::moveYoneticiIterByPageNumber(YoneticiList* yonetici)
{
	Node* YoneticiIter = yonetici->getAddr();

	int iterNumber = 1 + ((CurrentPageNumber - 1) * 8);

	for (int i = 0; i < iterNumber; i++)
	{
		YoneticiIter = YoneticiIter->next;
	}
	return YoneticiIter;

}


void UIx::UI_Satir(YoneticiList* yonetici)
{
	

	int gap = (iterCurrentIndex - 1) % 8;
	
	col = 12; // her bir sat�r i�in 6 birim (kendi uzunlugu) + 2 birim (arada bo�luk i�in keyfi) a�a��ya in


	Node* SatirIter = goToSatir2(yonetici);
	SatirIter = SatirIter->next; // head degerlerini gostermemek icin
	while (SatirIter != 0) {

		
		SetCursorPosition(row * gap, col + 0); cout << "|" << setw(14) << SatirIter << "|" << endl;
		SetCursorPosition(row * gap, col + 1); cout << "---------------" << endl;
		SetCursorPosition(row * gap, col + 2); cout << "|" << setw(14) << SatirIter->data << "|" << endl;
		SetCursorPosition(row * gap, col + 3); cout << "---------------" << endl;
		SetCursorPosition(row * gap, col + 4); cout << "|" << setw(14) << SatirIter->next << "|" << endl;
		SetCursorPosition(row * gap, col + 5); cout << "---------------" << endl;


		SatirIter = SatirIter->next;
		col = col + 7;//kendi uzunlugu 6, aralık olarak 1 bosluk verdik.
	}
	lastState = col;
	//col = 2;



}



Node* UIx::goToSatir2(YoneticiList* yonetici)
{
	Node* YoneticiIter = yonetici->getAddr();
	Node* Addr;

	for (int i = 0; i < iterCurrentIndex; i++)
	{
		YoneticiIter = YoneticiIter->next;
	}

	Addr = YoneticiIter->addr;

	return Addr;

}

void UIx::UI_Selector(int Index)
{

	int gap = (iterCurrentIndex - 1) % 8;


	// rasgele silme islemi oldugunda, text ifadeyi konuma gore yer degistirdim
	// 1-4 arasında |..........| <--- silinecek secili
	// 5-8 arasında silinecek secili ---> |...........|
	if(iterCurrentIndex % 8 > 4 || iterCurrentIndex % 8 == 0 )
	{
		SetCursorPosition(row*gap-24, 15 + (Index-1)*7 ); cout << " silinecek secili --->" << endl;
	}
	else
	{
		SetCursorPosition(row*gap+18, 15 + (Index-1)*7 ); cout << " <--- silinecek secili" << endl;
	}

	// silinecek secili ifadesi yerlestirilden sonra imleci onceki konumuna getiriyorum.
	SetCursorPosition(row*gap, lastState );

}

void SetCursorPosition(char x, char y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}