/**
* @file Sistem.cpp
* @description Organ sinifini tutan siniftir. Olusturuldugunda organlarý da olusturur.
* @course 2.Öðretim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak Gün, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Sistem.hpp"

Sistem::Sistem()
{
	organlar = new Organ[100];
}

Sistem::~Sistem()
{
	delete[] organlar;
}

