// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

typedef TArray<TArray<int>> TArray2D;

class MarkovChain
{

public:
	MarkovChain();
	~MarkovChain();

	/*
	* @brief Generate the list of ints representing the states
	*/
	void GenerateStatesArray();

	/*
	* @brief Get the array of states to process for chunk generation and setting texture
	*/
	TArray<int> GetStates();

	/*
	* @brief Set the number of states to generate
	*/
	void SetNumStates();

	/*
	* Update current state to the next after looking at the transition matrix
	*/
	void NextState();

	TArray<int> states;

protected:

private:
	int numStates;
	int current_state;
	int iterations;
	double transition_matrix[3][3] = { {0.2, 0.2, 0.6}, {0.1, 0.3, 0.6}, {0.1, 0.2, 0.8} };
};