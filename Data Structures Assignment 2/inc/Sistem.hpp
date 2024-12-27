#ifndef SISTEM_HPP
#define SISTEM_HPP

#include "Organ.hpp"

class Sistem{
	private:
		
		int length;
	public:
		Sistem();
		~Sistem();
		void Add(int value);
		Organ* organlar;
};
#endif // SISTEM_HPP