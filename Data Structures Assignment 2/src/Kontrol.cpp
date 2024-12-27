/**
* @file Kontrol.cpp
* @description Dosyayý okumaktan, olusturulan iki arama agacini mutasyona ugratmaktan ve ekrana yazdirmaktan sorumludur.
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Kontrol.hpp"
#include <iostream>

using namespace std;

Kontrol::Kontrol(Organizma* &org)
{
	this->organizma = org;
	SistemSayisi =0;

	OrganSayisi=0;
	DokuSayisi=0;
	HucreSayisi=0;
}
Kontrol::Kontrol(string dosya)
{
	FileName = dosya;
	int dosyaBoyutu = DosyaBoyutu(dosya);
	organizma = new Organizma(dosyaBoyutu/2000);

	SistemSayisi =0;
	OrganSayisi=0;
	DokuSayisi=0;
	HucreSayisi=0;
}
Kontrol::~Kontrol()
{
	delete organizma;
}

void Kontrol::OrganizmaYazdir(string msg=" ")
{	
	system("cls");
	cout<<endl;
	cout<<setw(45)<< msg;
	cout<<endl;
	cout<<endl;

	int SistemUzunluk = SistemSayisi ;
	for(int i = 0; i< SistemUzunluk; i++)
	{
		for(int j = 0; j< 100; j++)
		{

			int solYukseklik = organizma->sistemler[i].organlar[j].LeftHeight();
			int sagYukseklik = organizma->sistemler[i].organlar[j].RightHeight();

			if( abs(solYukseklik-sagYukseklik) >= 2)
			{
				cout<<"#";
			}
			else
			{
				cout<< " " ;
			}
		}

		cout << endl;
		
	}
}

void Kontrol::OrganizmaMutasyon()
{
	cout<<endl;
	int SistemUzunluk = SistemSayisi ;

	for(int i = 0; i< SistemUzunluk; i++)
	{
		for(int j = 0; j< 100; j++)
		{
			//cout << "["<<i<<"]"<< "["<<j<<"]"<< ": ";
			int len =organizma->sistemler[i].organlar[j].dokular[0].Size();
			int mid = organizma->sistemler[i].organlar[j].dokular[0].ElementAt((len+1)/2 -1);
			//cout<<mid<<":";
			if(mid % 50 == 0)
			{
			
				
				// Dokularýn hucre degerleri yarýya indirildi
				for(int c = 0; c<20; c++)
				{
					// dokunun veri uzunlugunu bul
					int sizeOfDoku = organizma->sistemler[i].organlar[j].dokular[c].Size();

					//***********************delete islemi duzeltilecek****************
					organizma->sistemler[i].organlar[j].Clear();
					// doku icerisinde veriler 2ye bolunuyorsa 2ye bol, olmazsa bir sey yapma
					for(int index = 0 ; index< sizeOfDoku; index++)
					{
						int deger = organizma->sistemler[i].organlar[j].dokular[c].ElementAt(index) ;
						if( deger % 2 == 0 )
						{	
							organizma->sistemler[i].organlar[j].dokular[c].ChangeAt(index,deger/2);
							
						}
						int mid = organizma->sistemler[i].organlar[j].dokular[c].ElementAt((sizeOfDoku+1)/2 -1);
						organizma->sistemler[i].organlar[j].Add(mid);
					}	
				}
			
			}

		}
	}
}

int Kontrol::DosyaBoyutu(string dosya)
{

	FileTxt.open(dosya);

	if (!FileTxt)
	{
		cout << "Dosya okuma islemi basarisiz oldu !! Dosya yolunu kontrol et ";
		return -1;
	}

	
	string line;
	unsigned long int linesize=0;
	while (FileTxt && getline(FileTxt, line) )
	{
		linesize++;
	}
	FileTxt.close();

	return linesize;
}



void Kontrol::SiralaVeEkle()
{
	ArrayList* RadixList = new ArrayList();

	FileTxt.open(FileName);
	string line;
	while (FileTxt && getline(FileTxt, line) )
	{
		string var;
		stringstream ss(line);

		//Her bir doku icerisindeki hucre uzunlugunu bulmak icin
		HucreSayisi = 0;
		RadixList->Clear();
		while (ss && ss >> var)
		{
			Hucre* hucre = new Hucre();
			hucre->item = stoi(var) ;

			//Siralama yapmak icin verilerin eklenmesi
			RadixList->Add( hucre->item )  ;

			delete hucre;

			HucreSayisi++;
			
		}
		
		int *RadixRastgele = new int[HucreSayisi];
		for(int i = 0; i< HucreSayisi; i++)
		{
			RadixRastgele[i] = RadixList->ElementAt(i);
		}
		Radix *radix = new Radix(RadixRastgele,HucreSayisi);
		int *RadixSirali = radix->Sort();
		

		

		 //Dokularin sirali olarak doku listesine eklenmesi
		for(int i = 0; i< HucreSayisi; i++)
		{
			organizma->sistemler[SistemSayisi].organlar[OrganSayisi].dokular[DokuSayisi].Add( RadixSirali[i] ) ;
		}


		//Sirali listenin ortasindaki degerin organ listesine eklenmesi
		organizma->sistemler[SistemSayisi].organlar[OrganSayisi].Add(  RadixSirali[ (HucreSayisi+1)/2 -1 ] );
		//cout << "hucreSayisi:"<<HucreSayisi<<"ort:"<< sirali[ (HucreSayisi+1)/2 -1 ] << endl;

		DokuSayisi = DokuSayisi % 20;
		DokuSayisi++;

		if(DokuSayisi == 20) 
		{
			DokuSayisi = 0;
			OrganSayisi++;			
			if(OrganSayisi % 100 == 0)
			{
				OrganSayisi=0;
				SistemSayisi++;
			}
			
		}
		delete[] RadixRastgele;
		delete[] RadixSirali;

		
	}
	FileTxt.open(FileName);


}
