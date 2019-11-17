//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// RngGen.cpp
//
// This file will define the class in RngGen.hpp
//
// ----------------------------------------------

#include"RngGen.hpp"
/*****************************************************
 * RngGen Overloaded Constructor
*****************************************************/
RngGen::RngGen(int min, int max) : min(min),
    				   max(max),
				   rng(rd()),
				   dis(std::uniform_int_distribution<>(min, max))
{}

/*****************************************************
 * GetRngNum()
 *
 * method to retrieve a random integer
 *
 * Params : N/A
 * Returns : int
*****************************************************/
int RngGen::GetRngNum()
{
	return dis(rng);
}


