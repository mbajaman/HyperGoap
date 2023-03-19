// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkovChain.h"
#include "Chunk/Chunk.h"

AMarkovChain::AMarkovChain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void AMarkovChain::BeginPlay()
{
	Super::BeginPlay();
}

void AMarkovChain::GenerateStatesArray()
{
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

TArray<int> AMarkovChain::GetStates()
{
	return states;
}

void AMarkovChain::SetNumStates()
{
}


