// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkovChain.h"

MarkovChain::MarkovChain()
{
	states.SetNum(100);
	size = 100;
	current_state = 0;
}

MarkovChain::MarkovChain(int Size)
{
	states.SetNum(Size);
	size = Size;
	current_state = 0;
}

MarkovChain::~MarkovChain()
{
	states.Empty();
}

void MarkovChain::GenerateStatesArray()
{
	states.Empty();
	for (int i = 0; i < size; i++)
	{
		double random_number = static_cast<double>(rand()) / RAND_MAX;

		current_state = NextState(random_number);
		states.Add(current_state);
	}
}

TArray<int> MarkovChain::GetStates()
{
	return states;
}

int MarkovChain::GetSize()
{
	return size;
}

void MarkovChain::SetNumStates()
{
	// Set number of states to generate
	size = 100;
}

int MarkovChain::NextState(double rand_n)
{
	UE_LOG(LogTemp, Warning, TEXT("Random Number in NextState: %f"), rand_n);
	// Move to next state
	if (rand_n <= transition_matrix[current_state][0])
	{
		next_state = 0;
	}
	else if (rand_n <= transition_matrix[current_state][0] + transition_matrix[current_state][1])
	{
		next_state = 1;
	}
	else if (rand_n <= transition_matrix[current_state][0] + transition_matrix[current_state][1] + transition_matrix[current_state][2])
	{
		next_state = 2;
	}
	else if (rand_n <= transition_matrix[current_state][0] + transition_matrix[current_state][1] + transition_matrix[current_state][2] + transition_matrix[current_state][3])
	{
		next_state = 3;
	}
	else if (rand_n <= transition_matrix[current_state][0] + transition_matrix[current_state][1] + transition_matrix[current_state][2] + transition_matrix[current_state][3] + transition_matrix[current_state][4])
	{
		next_state = 4;
	}
	else {
		next_state = 0;
	}

	return next_state;
}
