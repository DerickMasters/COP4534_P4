//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// BatchMonteCarlo.hpp
//
// This file will impliment a Monte Carlo
// algorithm to analyze micro chips to determine
// if a batch contains bad chips and the 
// confidence factor of that decision
//
// ----------------------------------------------

#ifndef BATCHMONTECARLO
#define BATCHMONTECARLO

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

#ifndef STRING
#define STRING

#include<string>

#endif

class BatchMonteCarlo
{
	public:
		BatchMonteCarlo();
		~BatchMonteCarlo();
		
		void ProcessBatchData(std::string specFileName);
		void PrintDataSetResults();

	private:	
		double CalcPercentProbFail(double p, int n);
		double CalcPercentTrueDetect(int detect, int total);
		int numBatches;
		int numItems;
		int pBadBatches;
		int pBadItems;
		int numSampled;
		RngGen* rng;
		std::vector<std::vector<char>*> batchData;
		std::vector<std::string> batchResults;
};

#endif
