//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// GenBatchDataSet.cpp
//
// This file will define the class in 
// GenBatchDataSet.hpp
//
// ----------------------------------------------

#include"GenBatchDataSet.hpp"

/*****************************************************
 * GenBatchDataSet Default Constructor
*****************************************************/
GenBatchDataSet::GenBatchDataSet()
{
	this->numBatches = 0;
	this->numItems = 0;
	this->pBadBatches = 0;
	this->pBadItems = 0;
	this->numSampled = 0;
	this->rngB = nullptr;
	this->rngI = new RngGen(0, 99);
}

/*****************************************************
 * GenBatchDataSet Destructor
*****************************************************/
GenBatchDataSet::~GenBatchDataSet()
{
	delete this->rngB;
	delete this->rngI;
}

/*****************************************************
 * ReadSpecs
 *
 * method to read in a test file and create a data
 * set depending on the contents of the test file
 *
 * Params : std::string specFileName
 * Returns : void
*****************************************************/
void GenBatchDataSet::ReadSpecs(std::string specFileName)
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
	this->rngB = new RngGen(0, this->numBatches-1);
//Close spec file
	specFile.close();
}

/*****************************************************
 * ProduceData
 *
 * method to create data set depending on spec file
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void GenBatchDataSet::ProduceData()
{
//Determine randomly which batches are bad
	for(int i = 0; i < (this->numBatches * this->pBadBatches)/100; i++)
	{
	//Variable to flag non unique index
		bool unique;
	//Generate random number for index
		int buffer = this->rngB->GetRngNum();
		do
		{
		//Check if random number index is already included in vector
			unique = true;
			if(!this->badBatches.empty())
			{
				for(std::vector<int>::size_type j = 0; j < this->badBatches.size(); j++)
				{
					if(this->badBatches.at(j) == buffer)
					{
						buffer = this->rngB->GetRngNum();
						unique = false;
						break;
					}
				}
			}
		}while(!unique);
	//Add unique index to vector
		this->badBatches.push_back(buffer);
	}	
//Loop to create each set of batch data
	for(int i = 0; i < this->numBatches; i++)
	{
	//Variable to flag bad batch
		bool bad = false;
	//Open output file to write to
		std::ofstream outFile;
		outFile.open(("ds" + std::to_string(i+1) + ".txt").c_str(), std::ofstream::out);
	//Check if batch is bad
		for(std::vector<int>::size_type j = 0; j < this->badBatches.size(); j++)
		{
			bad = false;
			if(i+1 == this->badBatches.at(j))
			{
				bad = true;	
				break;
			}
		}
	//If batch good write all good items
		if(!bad)
		{
			for(int l = 0; l < this->numItems; l++)
			{
				outFile << 'g' << "\n";
			}
		}
	//If bad determine bad items
		else if(bad)
		{
			for(int k = 0; k < this->numItems; k++)
			{
				outFile << GetItem(this->pBadItems) << "\n";
			}

		}
		outFile.close();
	}
}

/*****************************************************
 * PrintSpecs
 *
 * method print specs to console
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void GenBatchDataSet::PrintSpecs()
{
//Output specs to console
	std::cout << "Number of batches of items:                      " << this->numBatches << std::endl;
	std::cout << "Number of items in each batch:                   " << this->numItems << std::endl;
	std::cout << "Percentage of batches containing bad items:      " << this->pBadBatches << "%" << std::endl;
	std::cout << "Percentage of Items that are bad in a bad batch: " << this->pBadItems << "%" << std::endl;
	std::cout << "Items sampled from each set:                     " << this->numSampled << std::endl << std::endl;		
}

/*****************************************************
 * PrintData
 *
 * method to print bad batches to console
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void GenBatchDataSet::PrintData()
{
	for(std::vector<int>::size_type i = 0; i < this->badBatches.size(); i++)
	{
	//Variable to count how many items are bad in batch
		int numBad = 0;
	//open bad batch file
		std::ifstream batchFile;
		batchFile.open(("ds" + std::to_string(this->badBatches.at(i)) + ".txt").c_str(), std::ifstream::in);
	//Print Data to console
		for(int j = 0; j < this->numItems; j++)
		{
		//Count number of bad items in batch
			char buffer;
			batchFile >> buffer;
			if(buffer == 'b')
			{
				numBad++;
			}
		}
	//Print data
		std::cout << "Create bad batch # " << std::setw(3) << this->badBatches.at(i)
			  << ", totBad = " << numBad
			  << ", total = " << this->numItems
			  << ", badpct = " << this->pBadItems << std::endl;
	//Close bad batch file
		batchFile.close();	
	}
//Print total bad sets
	std::cout << "Total bad batches = " << this->badBatches.size() << std::endl << std::endl;
	this->badBatches.clear();	
}

/*****************************************************
 * GetItem
 *
 * helper method to produce an item depending on the
 * percent of bad items specified
 *
 * Params : int pBadItems
 * Returns : char
*****************************************************/
char GenBatchDataSet::GetItem(int pBadItems)
{
	if(this->rngI->GetRngNum() <= pBadItems)
	{
		return 'b';
	}
	else
	{
		return 'g';
	}
}

