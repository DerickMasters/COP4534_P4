//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// GenBacteriaDataSet.cpp
//
// This file will define the class in 
// GenBacteriaDataSet.hpp
//
// ----------------------------------------------

#include"GenBacteriaDataSet.hpp"

/*****************************************************
 * GenBacteriaDataSet Default Constructor
*****************************************************/
GenBacteriaDataSet::GenBacteriaDataSet()
{
	this->numDays = 0;
	this->numCategories = 0;
	this->rngR = new RngGen(2, 6);
	this->rngO = nullptr;
}

/*****************************************************
 * GenBacteriaDataSet Destructor
*****************************************************/
GenBacteriaDataSet::~GenBacteriaDataSet()
{
	delete this->rngR;
	delete this->rngO;
}

/*****************************************************
 * ProduceData
 *
 * method to create bacteria data set
 *
 * Params : int numDays, int numCategories, std::string dataFileName
 * Returns : void
*****************************************************/
void GenBacteriaDataSet::ProduceData(int numDays, int numCategories, std::string dataFileName)
{
//Save specs
	this->numDays = numDays;
	this->numCategories = numCategories;
//Open output data file
	std::ofstream dataFile;
	dataFile.open(dataFileName, std::ofstream::out);
//Variable to hold max of previous category
	int prevCat = 0;
//Initialize Rng generator for Occurances
	this->rngO = new RngGen(0, numCategories-1);
//Produce Occurances of each category
	std::vector<int> tempOccurrences(numCategories, 0);
	for(int i = 0; i < numDays; i++)
	{
		int tempIndex = this->rngO->GetRngNum();
		tempOccurrences.at(tempIndex)++;
	}
//Produce data
	dataFile << numDays << "\n";
	dataFile << numCategories << "\n";
	for(int j = 0; j < numCategories; j++)
	{
		std::string tempCat;
		int tempMax = this->rngR->GetRngNum()*1000;
		int tempOccures = tempOccurrences.at(j);
		tempCat = std::to_string(prevCat) + "-" + std::to_string(prevCat+tempMax) + ":" + std::to_string(tempOccures);
		dataFile << tempCat << "\n";
		this->categories.push_back(tempCat);
		prevCat += tempMax;
	}
	dataFile << "ml" << "\n";
		
//Close data file
	dataFile.close();
}

/*****************************************************
 * PrintSpecs
 *
 * method to prit to console specifications of 
 * data set
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void GenBacteriaDataSet::PrintSpecs()
{		
	std::cout << "Simulated days: " << this->numDays << std::endl;
	std::cout << "Number of categories: " << this->numCategories << std::endl;
}

/*****************************************************
 * PrintData
 *
 * method print data to console
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void GenBacteriaDataSet::PrintData()
{
	std::cout << "Ranges and occurrences in each range: " << std::endl;
	for(std::vector<std::string>::size_type i = 0; i < this->categories.size(); i++)
	{
		std::cout << categories.at(i) << std::endl;
	}	
	std::cout << "Units of measure: ml" << std::endl;
}

