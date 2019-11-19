//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// BacteriaMonteCarlo.cpp
//
// This file will define the class in 
// BacteriaMonteCarlo.hpp
//
// ----------------------------------------------

#include"BacteriaMonteCarlo.hpp"

/*****************************************************
 * BacteriaMonteCarlo Default Constructor
*****************************************************/
BacteriaMonteCarlo::BacteriaMonteCarlo()
{
	this->numDays = 0;
	this->numCategories = 0;
	this->units = "ml";
	this->analyticResult = 0.0;
	this->simResult = 0.0;
	this->rng = new RngGen(1, 100);
	this->rangeMin = 0;
	this->rangeMax = 1;
	this->rangeOccurs = 2;
	this->rangeMean = 3;
	this->probOccur = 4;
	this->cumulativeProb = 5;
	
}

/*****************************************************
 * BacteriaMonteCarlo Destructor
*****************************************************/
BacteriaMonteCarlo::~BacteriaMonteCarlo()
{
	delete this->rng;
	for(std::vector<std::vector<double>*>::size_type i = 0; i < this->categoryData.size(); i++)
	{
		delete this->categoryData.at(i);
	}	
}

/*****************************************************
 * ProcessBacteriaData
 *
 * method to analyze the supplied text file
 *
 * Params : std::string bacteriaFileName
 * Returns : void
*****************************************************/
void BacteriaMonteCarlo::ProcessBacteriaData(std::string bacteriaFileName)
{
//Open Data File
	std::ifstream dataFile;
	dataFile.open(bacteriaFileName, std::ifstream::in);
//Get Specs
	dataFile >> this->numDays;
	dataFile >> this->numCategories;
//Parse categories
	double cProbBuff = 0;
	for(int i = 0; i < this->numCategories; i++)
	{
		std::vector<double>* newCat = new std::vector<double>();	
		std::string categoryStr;
		dataFile >> categoryStr;
		std::string one;
		std::string two;
		std::string three;
		std::stringstream parseCat(categoryStr);
		std::getline(parseCat, one, '-');
		newCat->push_back(str_double(one));
		std::getline(parseCat, two, ':');
		newCat->push_back(str_double(two));
		std::getline(parseCat, three, '\n');
		newCat->push_back(str_double(three));

	//Calculate other attributes of category
		newCat->push_back((newCat->at(this->rangeMin)+newCat->at(rangeMax)*1.0)/2.0);
		newCat->push_back(CalcProbOccur(newCat->at(this->rangeOccurs)));
		cProbBuff += newCat->at(this->probOccur);
		newCat->push_back(cProbBuff);
	//add category to category list
		this->categoryData.push_back(newCat);	
	}
//Get units
	dataFile >> this->units;
//Calculate Analytic result
	CalcAnalytic();	
//Calculate Simulation result
	Simulate();	
//Close data file
	dataFile.close();
}

/*****************************************************
 * PrintBacteriaResults
 *
 * method to print to console the results of the 
 * analytical model and the simulation
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void BacteriaMonteCarlo::PrintBacteriaResults()
{		
//Determine analytic range
	std::string range;
	for(std::vector<std::vector<double>*>::size_type i = 0; i < this->categoryData.size(); i++)
	{
		if(this->analyticResult < this->categoryData.at(i)->at(rangeMax))
		{
			range = std::to_string(static_cast<int>(this->categoryData.at(i)->at(rangeMin))) + "-"
				+ std::to_string(static_cast<int>(this->categoryData.at(i)->at(rangeMax))) + "/"
				+ this->units + " range.";
			break;	
		}
	}
	std::cout << "Analytical model: " << std::setprecision(7) << this->analyticResult << ".";
	std::cout << " Expected value is in the " << range << std::endl;

	for(std::vector<std::vector<double>*>::size_type j = 0; j < this->categoryData.size(); j++)
	{
		if(this->simResult < this->categoryData.at(j)->at(rangeMax))
		{
			range = std::to_string(static_cast<int>(this->categoryData.at(j)->at(rangeMin))) + "-"
				+ std::to_string(static_cast<int>(this->categoryData.at(j)->at(rangeMax))) + "/"
				+ this->units + " range.";
			break;	
		}
	}

	std::cout << "Simulation: " << this->simResult << ".";
        std::cout << " Expected value is in the " << range << std::endl;
}

/*****************************************************
 * CalcProbOccur
 *
 * helper method to calculate the probability of
 * a range occuring
 *
 * Params : double rangeOccurs
 * Returns : double
*****************************************************/
double BacteriaMonteCarlo::CalcProbOccur(double rangeOccurs)
{	
	return (rangeOccurs/this->numDays);
}

/*****************************************************
 * CalcAnalytic
 *
 * helper method to calculate the analytic prediction
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void BacteriaMonteCarlo::CalcAnalytic()
{
	double tempAnalytic = 0;
	for(std::vector<std::vector<double>*>::size_type i = 0; i < this->categoryData.size(); i++)
	{
		tempAnalytic += (this->categoryData.at(i)->at(this->probOccur) * 
				 this->categoryData.at(i)->at(this->rangeMean));
	}
	this->analyticResult = tempAnalytic;
}

/*****************************************************
 * Simulate
 *
 * helper method to calculate the simulation prediction
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void BacteriaMonteCarlo::Simulate()
{
	double rangeSimMean = 0;
	for(int i = 0; i < this->numDays; i++)
	{
		int simNum = this->rng->GetRngNum();
		for(std::vector<std::vector<double>*>::size_type j = 0; j < this->categoryData.size(); j++)
		{
			std::vector<double>* tempPtr = this->categoryData.at(j);
			if(simNum < tempPtr->at(this->cumulativeProb)*100)
			{
				rangeSimMean += (tempPtr->at(this->rangeMean));
				break;
			}
		}
	}	
	this->simResult = rangeSimMean/this->numDays;
}

/*****************************************************
 * str_double
 *
 * helper method to convert a string into a double
 * without rounding the resultant double
 *
 * Params : std::string inStr
 * Returns : double
*****************************************************/
double BacteriaMonteCarlo::str_double(std::string inStr)
{
	double result = 0;
	double place = 1;
	for(int i = inStr.size()-1; i >= 0; i--)
	{
		result += ((inStr[i]-'0')*place);
		place = place * 10;
	}
	return result;
}


