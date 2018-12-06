#pragma once
//#include "Genes.h"
#include <vector>
#include <ctime>
#include <random>
template <typename T, int NEW_GENES,  int POPULATION, int RANDOMISE>

class GASystem  
{
	using Chromosome = std::vector<T>;
public:
	float fitnessscore[POPULATION];
	// gets the current population 
	std::vector<Chromosome>& getpopulation() { return populationVector; }
	
	const std::vector<Chromosome>& getpopulation() const { return populationVector; }

	void Population()
	{

		for (int i = 0; i < POPULATION; i++)
		{ 
			CreateChromosome();
			//Pushes Chromosomes into the Population
			populationVector.push_back(chromosomevector);
			
			fitnessscore[i] = 0.0f;

		}
	}
	void FitnessFunction()
	{
		//Cleans out the parent vector to take in new population vector
		ParentVector.clear();
	  	ParentVector = populationVector;

		//Population vector will be used later to hold new children population 
	  	populationVector.clear();
		
		//Gets two of the strongest parents
		for (int i = 0; i < ParentVector.size() / 2; i++)
	  	{
			// gets four random numbers from the POPULATION
			int ParentOne = rand() % POPULATION;
			int ParentTwo = rand() % POPULATION;
			int ParentThree = rand() % POPULATION;
			int ParentFour = rand() % POPULATION;
			// if the fitnessscore of Parentone is less than Parent 2
			// push it into the CrossoverParentVector
	  		if (fitnessscore[ParentOne] <= fitnessscore[ParentTwo])
	  		{
	  			CrossoverParentVector.push_back(ParentVector[ParentOne]);
	  		}
	  		else
	  		{

				CrossoverParentVector.push_back(ParentVector[ParentTwo]);
	  
	  		}
			// if the fitnessscore of Parentone is less than Parent 2
			// push it into the CrossoverParentVecotr
			if (fitnessscore[ParentThree] <= fitnessscore[ParentFour])
			{
				CrossoverParentVector.push_back(ParentVector[ParentThree]);
			}
			else
			{
				CrossoverParentVector.push_back(ParentVector[ParentFour]);
		
			}
			// adds in the two strongest parents and crosses their genes
			Crossover(CrossoverParentVector[0], CrossoverParentVector[1]);

		}
		CrossoverParentVector.clear();
		Mutate(); 
	}
private: 

	void CreateChromosome()
	{
		
		Chromosome chromosome;
		// Creates chromosomes out of possible genes
		for (int CurrentChromosome = 0; CurrentChromosome < NEW_GENES; CurrentChromosome++)
		{
			// gets a random genes out of the enum
			T randomgene = static_cast<T>(rand() % T::NUM_VALUES);
			chromosome.push_back(randomgene);
		}
		//adds list of random chromosomes into a vector
		chromosomevector = chromosome;

	}

	// Takes 2 parent solutions and makes a child from them,
	void Crossover(std::vector<T> firstParent , std::vector<T> secondParent)
	{
		Chromosome firstChild;
		Chromosome secondChild;

		int half_size = NEW_GENES / 2;
		// adds half of parent one and parent two into a new child
		for (int i = 0; i < NEW_GENES; i++)
		{	
			if (i < half_size)
			{
				firstChild.push_back(firstParent[i]);
				secondChild.push_back(secondParent[i]);
			}
			else
			{
				firstChild.push_back(secondParent[i]);
				secondChild.push_back(firstParent[i]);
			}
		
		}
		populationVector.push_back(firstChild);
		populationVector.push_back(secondChild);
	}
	
	void Mutate()
		{
		// goes through entire population looking for a chromosome to mutate
			for(auto& chromosome : populationVector)
			{
				const int MUTATION_RATE = 3;
				const int MUTATION_CHANCE = 5;

				int random = rand() % 100;
				// The chance of mutation
				if (random < MUTATION_CHANCE)
				{
					for (auto& gene : chromosome)
					{
						random = rand() % 100;
						// the chance of a gene being mutated 
						if (random < MUTATION_RATE)
						{
							T randomGene = static_cast<T>(rand() % T::NUM_VALUES);
							gene = randomGene;
						}
					}
				
				}
			}
		}
	
	//Holds the Chromosomes 
	Chromosome chromosomevector;
	//Holds current population of Chromosomes 
	std::vector<Chromosome> populationVector;
	//Holds the Parent chromosomes to test fitness 
	std::vector<Chromosome> ParentVector;
	//Holds the Chromosomes which will be used for mating
	std::vector<Chromosome> CrossoverParentVector;
	
};