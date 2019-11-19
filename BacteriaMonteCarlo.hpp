//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// BacteriaMonteCarlo.hpp
//
// This file will utilize a Monte Carlo algorithm
// to analyze historical readings of bacteria
// populations to predict the expected 
// bacterial reading
//
// ----------------------------------------------

#ifndef BACTERIAMONTECARLO
#define BACTERIAMONTECARLO

#include"RngGen.hpp"

#ifndef VECTOR
#define VECTOR

#include<vector>

#endif

#ifndef FSTREAM
#define FSTREAM

#include<fstream>

#endif

#ifndef IOSTREAM
#define IOSTREAM

#include<iostream> //TEST

#endif

#ifndef IOMANIP
#define IOMANIP

#include<iomanip>

#endif

#ifndef SSTREAM
#define SSTREAM

#include<sstream>

#endif

class BacteriaMonteCarlo
{
	public:
		BacteriaMonteCarlo();
		~BacteriaMonteCarlo();
		
		void ProcessBacteriaData(std::string bacteriaFileName);
		void PrintBacteriaResults();	

	private:	
		double CalcProbOccur(double rangeOccurs);
		void CalcAnalytic();
		void Simulate();
		double str_double(std::string inStr);
		std::vector<std::vector<double>*> categoryData;
		int numDays;
		int numCategories;
		std::string units;
		double analyticResult;
		double simResult;
		RngGen* rng;

		int rangeMin;
		int rangeMax;
		int rangeOccurs;
		int rangeMean;
		int probOccur;
		int cumulativeProb;
};

#endif
