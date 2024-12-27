/**
* @file Test.cpp
* @description Verilen dosya yolunu okur, ekrana yazdýrýr, kullanýcýdan enter tuþuna basmasýný bekler ve organizmayý mutasyona ugratýr
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include <iostream>
#include "Kontrol.hpp"

using namespace std;

string dosya = "./Veri2.txt";

int main(){


	Kontrol * kontrol = new Kontrol(dosya);
	kontrol->SiralaVeEkle();
	kontrol->OrganizmaYazdir("ORGANIZMA");

	cout<< "Mutasyon icin Enter'a basin...";
	while(cin.get() == '\n')
	{
			kontrol->OrganizmaMutasyon();
			kontrol->OrganizmaYazdir("ORGANIZMA (MUTASYONA UGRADI)");
			break;
	}

	
	delete kontrol;

	return 0;

}





























