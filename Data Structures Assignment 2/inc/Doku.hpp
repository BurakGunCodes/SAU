#ifndef DOKU_HPP
#define DOKU_HPP

#include <iostream>
#include "ArrayList.hpp"
#include "Hucre.hpp"

class Doku : public ArrayList{
	private:
		
		
		int length;
	public:
	
		Doku();
		~Doku();
		
		ArrayList* dokular;


};
#endif // DOKU_HPP