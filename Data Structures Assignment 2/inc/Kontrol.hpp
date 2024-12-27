#ifndef KONTROL_HPP
#define KONTROL_HPP

#include "Organizma.hpp"
#include "Hucre.hpp"
#include "ArrayList.hpp"
#include "Radix.hpp"

#include <fstream>
#include <string>
#include <sstream>

#include <iomanip>

class Kontrol{
	private:

		fstream FileTxt;
		string FileName;
		int SistemSayisi;
		int OrganSayisi;
		int DokuSayisi;
		int HucreSayisi;
		
	public:
		Kontrol(Organizma* &org);
		Kontrol(string file);
		~Kontrol();
		Organizma* organizma;

	void OrganizmaYazdir(string);
	void OrganizmaMutasyon();
	int DosyaBoyutu(string file);
	void SiralaVeEkle();
};

#endif