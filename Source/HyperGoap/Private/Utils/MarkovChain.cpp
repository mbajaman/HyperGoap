// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkovChain.h"

MarkovChain::MarkovChain()
{
	states.SetNum(50);
	iterations = 49;
	current_state = 0;
}

MarkovChain::~MarkovChain()
{
	states.Empty();
}

void MarkovChain::GenerateStatesArray()
{
	states.Empty();
	for (int i = 0; i < iterations; i++)
	{
		double random_number = FMath::FRandRange(0.0, 1.0);

		// Move to next state
		if (random_number <= transition_matrix[current_state][0])
		{
			current_state = 0;
		}
		else if (random_number <= transition_matrix[current_state][0] + transition_matrix[current_state][1])
		{
			current_state = 1;
		}
		else
		{
			current_state = 2;
		}
		states.Add(current_state);
	}
}

TArray<int> MarkovChain::GetStates()
{
	return states;
}
