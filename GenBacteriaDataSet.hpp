//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// GenBacteriaDataSet.hpp
//
// This file will process instructions to create
// a data set of bacteria population range 
// occurances
//
// ----------------------------------------------

#ifndef GENBACTERIADATASET
#define GENBACTERIADATASET

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

#ifndef STRING
#define STRING

#include<string>

#endif

#ifndef IOMANIP
#define IOMANIP

#include<iomanip>

#endif

class GenBacteriaDataSet
{
	public:
		GenBacteriaDataSet();
		~GenBacteriaDataSet();
		
		void ProduceData(int numDays, int numCategories, std::string dataFileName);
		void PrintSpecs();
		void PrintData();	

	private:	
		std::vector<std::string> categories;
		int numDays;
		int numCategories;
		RngGen* rngR;
		RngGen* rngO;
};

#endif
