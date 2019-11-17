/*****************************************************************
 *
 *	Derick Masters
 *	COP4534_Data_structures
 *
 *	main.cpp
 *
 *	This file will utilize a MonteCarlo algorithm to solve
 *	two problems:
 *
 *	1) Detecting bad batches of micro-chips without testing
 *	   every single chip
 *	2) Determine the quantity range of bacteria in Escambia
 *	   bay depending on historical data
 *
*****************************************************************/

#include<iostream>
#include"GenBatchDataSet.hpp"
#include"GenBacteriaDataSet.hpp"
#include"BacteriaMonteCarlo.hpp"
#include"BatchMonteCarlo.hpp"
#include<vector>
#include<string>
#include<random>

int main()
{
//Variables
	std::vector<std::string> testFileNames = {"t1.txt", "t2.txt", "t3.txt", "t4.txt"};
;
	int numDays = 100;
	int numCategories = 7;
	std::string bacteriaDataFileName = "bacteria.txt";
//Instatiate Objects	
	GenBatchDataSet* gBatchDS = new GenBatchDataSet();
	GenBacteriaDataSet* gBacteriaDS = new GenBacteriaDataSet();
	BatchMonteCarlo* BatchMC = new BatchMonteCarlo();
	BacteriaMonteCarlo* BacteriaMC = new BacteriaMonteCarlo();

//Perform Batch Analysis
	for(unsigned int i = 0; i < testFileNames.size(); i++)
	{
		std::cout << "Simulation " << (i+1) << ":" << std::endl;
	//Generate Batch Data Set
		gBatchDS->ReadSpecs(testFileNames.at(i));
		gBatchDS->PrintSpecs();
		gBatchDS->ProduceData();
		gBatchDS->PrintData();
	//Analyze Batches From Data Set
		BatchMC->ProcessBatchData(testFileNames.at(i));
		BatchMC->PrintSpecs();
		BatchMC->PrintDataSetResults();
		std::cout << "End Simulation " << (i+1) << std::endl << std::endl;	
	}	

//Perform Bacteria Analysis
 	//GenBacteriaDataSets
	gBacteriaDS->ProduceData(numDays, numCategories, bacteriaDataFileName);
	gBacteriaDS->PrintSpecs();
	gBacteriaDS->PrintData();
	//Analyze Bacteria Data Set
	BacteriaMC->ProcessBacteriaData(bacteriaDataFileName);
	BacteriaMC->PrintBacteriaResults();		

//Free Memory
	delete gBatchDS;
	delete gBacteriaDS;
	delete BatchMC;
	delete BacteriaMC;
//Exit Program
	return 0;
}


