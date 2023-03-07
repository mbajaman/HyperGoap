// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMarkov.h"

SimpleMarkov::SimpleMarkov()
{
}

SimpleMarkov::~SimpleMarkov()
{
}

void SimpleMarkov::SampleRun()
{
	double transition_matrix[2][2] = { {0.7, 0.3}, {0.4, 0.6} };
	int current_state = 0;
	std::vector<int> states;
	int num_iterations = 10;

	UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), current_state);

	for (int i = 0; i < num_iterations; i++)
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
		states.push_back(current_state);
		SET_WARN_COLOR(COLOR_CYAN);
		UE_LOG(LogTemp, Warning, TEXT("Current state: %d"), current_state);

	}
}
