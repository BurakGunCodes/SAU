#ifndef RADIX_HPP
#define RADIX_HPP

#include "Queue.hpp"
#include <cmath>

class Radix{
	private:	
		int* numbers;
		int length;
		int maxStep;
		Queue** queues; //kuyruklar dizisi
		
		int MaxStepNumber();
		int StepCount(int);
		int* QueueCurrentLengths();
		int power(int e);
	public:
		Radix(int*, int);
		int* Sort();
		~Radix();
};

#endif // RADIX_HPP
