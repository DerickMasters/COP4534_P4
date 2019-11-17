//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// Tour.hpp
//
// This file will declare the aspects of the
// Tour object that will be a sequence of 
// CityRoutes 
//
// ----------------------------------------------

#ifndef TOUR
#define TOUR

#include"Matrix.hpp"

#ifndef VECTOR
#define VECTOR

#include<vector>

#endif

class Tour
{
	public:
		Tour();
		Tour(Matrix refMatrix);
		Tour(const Tour& tourCopy);
		~Tour();
		
		double GetCost();
		int at(int index);
		void Push_Back(int newCity);
		int size();
		void Swap(int source, int target);	
		void Shuffle();	

	private:
		std::vector<int>* path;
		Matrix* tourMatrix;
		double cost;
};

#endif
