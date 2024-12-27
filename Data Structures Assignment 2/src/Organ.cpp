/**
* @file Organ.cpp
* @description BST s�n�f�ntan kal�t�m almaktad�r. Doku degerlerinin orta eleman degerini tutan agactan olusmaktadir.
* @course 2.��retim A Grubu
* @assignment 2.Odev
* @date 23/12/2022
* @author Burak G�n, burak.gun1@ogr.sakarya.edu.tr
*/

#include "Organ.hpp"
#include <iostream>

Organ::Organ()
{
	dokular = new Doku[20];
}


Organ::~Organ()
{
	delete[] dokular;
}


