//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// BatchMonteCarlo.cpp
//
// This file will define the class in 
// BatchMonteCarlo.hpp
//
// ----------------------------------------------

#include"BatchMonteCarlo.hpp"

/*****************************************************
 * BatchMOnteCarlo Default Constructor
*****************************************************/
BatchMonteCarlo::BatchMonteCarlo()
{
	this->numBatches = 0;
	this->numItems = 0;
	this->pBadBatches = 0;
	this->pBadItems = 0;
	this->numSampled = 0;
	this->rng = nullptr;
}

/*****************************************************
 * BatchMonteCarlo Destructor
*****************************************************/
BatchMonteCarlo::~BatchMonteCarlo()
{
	delete this->rng;
	for(std::vector<std::vector<char>*>::size_type i = 0; i < this->batchData.size(); i++)
	{
		delete this->batchData.at(i);
	}

}

/*****************************************************
 * ProcessBatchData
 *
 * method to read in spec File and analyze data set
 *
 * Params : std::string specFileName
 * Returns : void
*****************************************************/
void BatchMonteCarlo::ProcessBatchData(std::string specFileName)
{
//Open spec file
	std::ifstream specFile;
	specFile.open(specFileName, std::ifstream::in);
//Retrieve specs
	this->numBatches = 0;
	this->numItems = 0;
	this->pBadBatches = 0;
	this->pBadItems = 0;
	this->numSampled = 0;

	specFile >> this->numBatches;
	specFile >> this->numItems;
	specFile >> this->pBadBatches;
	specFile >> this->pBadItems;
	specFile >> this->numSampled;
//Initialize RngGen with spec data
	this->rng = new RngGen(0, this->numBatches-1);
//Close spec file
	specFile.close();
//Analyze batches from dataset

	for(int i = 0; i < this->numBatches; i++)
	{
	//Retrieve batch data from data file
		std::ifstream batchDataFile;
		batchDataFile.open(("ds" + std::to_string(i+1) + ".txt").c_str(), std::ifstream::in);
		std::vector<char>* batch = new std::vector<char>();

		for(int j = 0; j < this->numItems; j++)
		{
			char tempChar;
			batchDataFile >> tempChar;
			batch->push_back(tempChar);
		}

		this->batchData.push_back(batch);
	//close batch data file
		batchDataFile.close();
	//Sample Batches


		for(int k = 0; k < this->numSampled; k++)
		{
		//Vector to hold which indecies to sample
			std::vector<int> sampleIndexes;
		//Variable to flag non unique index
			bool unique;
		//Generate random number for sample
			int buffer = this->rng->GetRngNum();
			do
			{
			//Check if random number index is already included in vector
				unique = true;
					for(std::vector<int>::size_type l = 0; l < sampleIndexes.size(); l++)
					{
						if(sampleIndexes.at(l) == buffer)
						{
							buffer = this->rng->GetRngNum();
							unique = false;
						}
					}
			}while(!unique);
		//Add unique index to vector
			sampleIndexes.push_back(buffer);
		//Check if good or bad item
			if(this->batchData.back()->at(buffer) == 'b')
			{
				this->batchResults.push_back("batch #" + std::to_string(i+1) + " is bad");
				break;
			}
		}
	}
}

/*****************************************************
 * PrintDataSetResults
 *
 * method to print results of analysis to console
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void BatchMonteCarlo::PrintDataSetResults()
{	
	std::cout << "Analyzing Batch Data:" << std::endl;
	for(std::vector<std::string>::size_type i = 0; i < this->batchResults.size(); i++)
	{
		std::cout << this->batchResults.at(i) << std::endl;
	}
	double p = (1 - (this->pBadItems/100.0));
	int n = this->numSampled;
	std::cout << "Base = " << p << " Exponent = " << n << std::endl;
	std::cout << "P(failure to detect bad batch) = " << CalcPercentProbFail(p, n) << std::endl;
	std::cout << "Percentage of bad batches actually detected = " << std::setw(3) <<std::setprecision(4) << CalcPercentTrueDetect(batchResults.size(), (this->pBadBatches * this->numBatches * 1.0) / 100.0) << "%" << std::endl << std::endl;
	this->batchResults.clear();


}

/*****************************************************
 * CalcPercentProbFail
 *
 * helper method to calculate the probability of failure to
 * detect if a batch is bad
 *
 * Params : double p, int n
 * Returns : double
*****************************************************/
double BatchMonteCarlo::CalcPercentProbFail(double p, int n)
{
	double product = 1;
	for(int i = 0; i < n; i++)
	{
		product = product * p;
	}
	return product;
}

/*****************************************************
 * CalcPercentTrueDetect
 *
 * helper method to determine how many of the bad
 * batches were actually detected
 *
 * Params : int detect, int total
 * Returns : double
*****************************************************/
double BatchMonteCarlo::CalcPercentTrueDetect(int detect, int total)
{
	double product;
	product = ((detect * 1.0)/total) * 100.0;
	return product;	
}


