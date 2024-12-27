/**
* @file Doku.cpp
* @description ArrayList.cpp sýnýfýndan kalýtým almaktadýr. Dosyada bulunan satirdaki degiskenleri saklar.
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Doku.hpp"
#include "Hucre.hpp"

Doku::Doku()
{
	length=0;
	dokular = new ArrayList[20];
	//static int x =0;
	//std::cout << ++x << " Adet Doku olustu" << std::endl;
}



Doku::~Doku()
{
	delete[] dokular;
}

