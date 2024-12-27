/**
* @file Organizma.cpp
* @description Dosya i�erisinde bulunan butun degerlere ulasilabilen, i�i�e s�n�f yap�s�n�n en �st hiyera�isinde bulunur. 
* @course 2.��retim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak G�n, burak.gun1@ogr.sakarya.edu.tr
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