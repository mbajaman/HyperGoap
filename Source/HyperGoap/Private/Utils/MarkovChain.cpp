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
		if (random_number < transition_matrix[current_state][0])
		{
			current_state = 0;
		}
		else
		{
			current_state = 1;
		}
		states.Add(current_state);
		// SET_WARN_COLOR(COLOR_CYAN);
		// UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), current_state);
	}
}

TArray<int> AMarkovChain::GetStates()
{
	return TArray<int>();
}

void AMarkovChain::SetNumStates()
{
}


