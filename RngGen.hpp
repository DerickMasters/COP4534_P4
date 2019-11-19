//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// RngGen.hpp
//
// This file will produce random integers
// from a uniform distribution 
//
// ----------------------------------------------

#ifndef RNGGEN
#define RNGGEN

#include<random>

class RngGen
{
	public:
		RngGen();
		RngGen(int min, int max);
		
		int GetRngNum();
		
	private:
		std::random_device rd;
		int min;
		int max;
		std::mt19937 rng;
		std::uniform_int_distribution<int> dis;
};

#endif
