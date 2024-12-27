/**
* @file Organizma.cpp
* @description Dosya içerisinde bulunan butun degerlere ulasilabilen, içiçe sýnýf yapýsýnýn en üst hiyeraþisinde bulunur. 
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/


#include "Organizma.hpp"

Organizma::Organizma()
{
	length=0;
	sistemler = new Sistem();
}

Organizma::Organizma(int k)
{
	length = k;
	sistemler = new Sistem[k];
}

Organizma::~Organizma()
{
	delete[] sistemler;
 }

 int Organizma::SistemUzunluk()
 {
	return length;
 }