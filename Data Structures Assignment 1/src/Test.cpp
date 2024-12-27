/** 
* @file Test.cpp
* @description Kodumuzu test ettigimiz ana dosyadir. Burada veriler text dosyasindan okunur, okunan veriler listeye atanir.
	Kullanicidan alýnan komutlara gore ekranda veriler gosterilir ve silme islemleri yapilir. 
	Kullanýcýdan 'x' girilmesi halinde veya listede eleman kalmamasý durumunda program sonlandýrýlýr.
* @course 2.Ogretim A Grubu
* @assignment Odev_1
* @date 24/11/2022
* @author Burak Gun, burak.gun1@ogr.sakarya.edu.tr
*/

#include <iostream>
#include "List.hpp"
#include "YoneticiList.hpp"
#include "UI.hpp"


//File I/O
#include <fstream>
#include <string>
#include <sstream>

#include<cstdlib>
#include <time.h>

using namespace std;

int verilerSatirSayisi = 0; 
int iterCurrentIndex = 1; // baslangic olarak ilk indexten basla
int selectorCount = 0;

int main()
{

	fstream file;
	file.open("./veriler.txt");

	if (!file)
	{
		cout << "Dosya okuma islemi basarisiz oldu !! Dosya yolunu kontrol et ";
		return -1;
	}

	/*****************************************************************************/

	 YoneticiList* yonetici = new YoneticiList;

	
	string line;

	while (file && getline(file, line) )
	{
		
		string var;
		stringstream ss(line);
		List* satir = new List;
		while (ss && ss >> var)
		{
			satir->Add(stoi(var));
		}

		yonetici->AddByAvg(satir, satir->GetAvgOfList());
	
	}
	
	file.close();

	/*****************************************************************************/
	
		 
	


	// henuz tusa basilmadan butun verileri oku ve ekrana yazdir
	verilerSatirSayisi = yonetici->Size();
	
	UIx UI;
	system("cls");
	UI.UI_Header();
	UI.UI_Yonetici(yonetici);
	UI.UI_Satir(yonetici);

	char input;
	

	do{


		cout << endl << "exit(x) secenek: ";
		cin.clear(); fflush(stdin);
		cin >> input;


		switch (input)
		{
			case 'z':
				if ( !(iterCurrentIndex <= 1) )//index degerini sýfýra düþürmemek için
				iterCurrentIndex--;
			break;

			case 'c':
				if ( !(iterCurrentIndex >= verilerSatirSayisi) ) // index degerinin dizinin uzunlugundan uzun olmamasý gerekir
					iterCurrentIndex++;
			break;

			case 'a':
				iterCurrentIndex = iterCurrentIndex - 8;
				if (iterCurrentIndex <= 1) iterCurrentIndex = 1;
			break;

			case 'd':
				iterCurrentIndex = iterCurrentIndex + 8;
				if (iterCurrentIndex >= verilerSatirSayisi) iterCurrentIndex = verilerSatirSayisi;
			break;

			case 'p':
				yonetici->RemoveSatir(yonetici);
				yonetici->RemoveYoneticiNodeAt();
			break;

			case 'k':
			{
				int sizeOfNodeX = yonetici->SizeOfNode(yonetici);
				srand(time(0));
				int randNum = (rand() % (sizeOfNodeX - 1)) + 1;

				UI.UI_Selector(randNum);

				cout << endl << "Silmek icin tekrar 'k' harfine basin: ";
				cin.clear(); fflush(stdin);
				cin >> input;
			
				if (input == 'k') {
				yonetici->RandomDelete(yonetici, randNum);
				}
				else 
				{
					;
				}

			}

			break;

			case 'x':
				cout << "Program kapatiliyor." << endl;
			break;

			default:
				cout << "Gecersiz karakter. Devam etmek icin bir tusa basin..." << endl;
				int dummy;
				cin>>dummy;
		}

		// Guncenl sayi degerleriyle islem yap
		verilerSatirSayisi = yonetici->Size();
		if(verilerSatirSayisi > 0)
		{
			system("cls");
			UI.UI_Header();
			UI.UI_Yonetici(yonetici);
			UI.UI_Satir(yonetici);
		}
		else
		{
			cout << "Yonetici Dizisinde Eleman Yoktur. "<< endl << "Program Sonlandiriliyor." << endl ;  
			// programi sonlandir
			input = 'x';
		}



	} while (input != 'x');

	// program bitiminde bellekte ver alan alanlar serbest birakiliyor 
	int size = yonetici->Size(); //yonetici->Size
	for ( int i = 1 ; i <= size ; i++)
	{
		iterCurrentIndex = 1;
		yonetici->RemoveSatir(yonetici);
		yonetici->RemoveYoneticiNodeAt();
	}

	cout << "Veriler basari ile silinmistir." << endl;
	

	return 0;
}