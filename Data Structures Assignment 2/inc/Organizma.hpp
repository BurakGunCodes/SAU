#ifndef ORGANIZMA_HPP
#define ORGANIZMA_HPP

#include "Sistem.hpp"

class Organizma{
	private:
		int length;
		
	public:
		Organizma();
		Organizma(int k);
		~Organizma();
		int SistemUzunluk();
		Sistem* sistemler;

};

#endif // ORGANIZMA_HPP