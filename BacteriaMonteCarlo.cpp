//-----------------------------------------------
// Derick Masters
// COP4534_Data_Structures
// Tour.cpp
//
// This file will define the class in Tour.hpp
//
// ----------------------------------------------

#include"Tour.hpp"
#include"Matrix.hpp"
#include<algorithm>
#include<random>

#include<iostream> //TEST

/*****************************************************
 * Tour Default Constructor
*****************************************************/
Tour::Tour()
{
	this->path = new std::vector<int>();
	this->tourMatrix = nullptr;
	this->cost = 0.00;
}

/*****************************************************
 * Tour Overloaded Constructor
*****************************************************/
Tour::Tour(Matrix refMatrix)
{
	this->path = new std::vector<int>();
	this->tourMatrix = &refMatrix;
	this->cost = 0.00;
}

/*****************************************************
 * Tour Copy Constructor
*****************************************************/
Tour::Tour(const Tour& tourCopy)
{
	this->path = tourCopy.path;
	this->tourMatrix = tourCopy.tourMatrix;
	this->cost = tourCopy.cost;
}


/*****************************************************
 * Tour Destructor
*****************************************************/
Tour::~Tour()
{
	delete this->path;
	delete this->tourMatrix;
}

/*****************************************************
 * GetCost
 *
 * method to retrieve total Cost of CityRoutes in
 * Tour
 *
 * Params : N/A
 * Returns : double
*****************************************************/
double Tour::GetCost()
{
	std::cout << "path->size() = " << this->path->size() << std::endl; //TEST
	for(int i = 0; i < this->path->size(); i++)
	{
		std::cout << "LOOPS :" << i << std::endl; //TEST
		if(i == (this->path->size() - 1))
		{
			int origin = this->path->at(i);
			int destination = this->path->at(0);
			this->cost += this->tourMatrix->GetCityRoute(origin, destination).GetDistance();
		}
		else
		{
			std::cout << "IN ELSE" << std::endl; //TEST
			int j = i + 1;
			int origin = this->path->at(i);
			int destination = this->path->at(j);
			this->cost += this->tourMatrix->GetCityRoute(origin, destination).GetDistance();
		}
	}
	return this->cost;
}

/*****************************************************
 * at
 *
 * method to retrieve element of path of Tour object
 *
 * Params : int index
 * Returns : int
*****************************************************/
int Tour::at(int index)
{
	return this->path->at(index);
}

/*****************************************************
 * push_back
 *
 * method to add a CityRoute to the back of the 
 * Tour path
 *
 * Params : CityRoute* newRoute
 * Returns : void
*****************************************************/
void Tour::Push_Back(int newCity)
{
	this->path->push_back(newCity);
}

/*****************************************************
 * size
 *
 * method to return size of Tour path
 *
 * Params : N/A
 * Returns : int
*****************************************************/
int Tour::size()
{
	return this->path->size();	
}

/*****************************************************
 * Swap
 *
 * helper method to swap content of vector at the 
 * passed indices.
 *
 * Params : int index, int parent
 * Returns : void
*****************************************************/
void Tour::Swap(int source, int target)
{
	int temp = this->path->at(target);
	this->path->at(target) = this->path->at(source);
	this->path->at(source) = temp;
}

/*****************************************************
 * Shuffle
 *
 * method to shuffle contents of Tour
 *
 * Params : N/A
 * Returns : void
*****************************************************/
void Tour::Shuffle()
{
	thread_local static std::random_device rd;
	thread_local static std::mt19937 gen(rd());
	std::shuffle(this->path->begin(), this->path->end(), gen);
}
