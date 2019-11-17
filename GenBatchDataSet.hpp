//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// GenBatchDataSet.hpp
//
// This file will process instructions to create
// a data set of microchip good/bad batches
//
// ----------------------------------------------

#ifndef GENBATCHDATASET
#define GENBATCHDATASET

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

class GenBatchDataSet
{
	public:
		GenBatchDataSet();
		~GenBatchDataSet();
		
		void ReadSpecs(std::string specFileName);
		void ProduceData();
		void PrintSpecs();
		void PrintData();	

	private:	
		void GetItem();
		int numBatches;
		int numItems;
		int pBadBatches;
		int pBadItems;
		int numSampled;
		RngGen* rngB;
		RngGen* rngI;
		std::vector<int> badBatches;
};

#endif
