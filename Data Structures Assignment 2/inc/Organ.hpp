#ifndef ORGAN_HPP
#define ORGAN_HPP

#include "BST.hpp"
#include "Doku.hpp"

// Ýkili arama agacý olacak
class Organ : public BST{
	private:
		
		int length;
	public:
		Organ();
		~Organ();
		Doku* dokular;
		
};

#endif // ORGAN_HPP