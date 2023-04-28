// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

typedef TArray<TArray<int>> TArray2D;

class MarkovChain
{

public:
	MarkovChain();
	MarkovChain(int Size);
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
	* @brief Get the size of the array of states
	*/
	int GetSize();

	/*
	* @brief Set the number of states to generate
	*/
	void SetNumStates();

	/*
	* Update current state to the next after looking at the transition matrix
	*/
	int NextState(double rand_n);

	TArray<int> states;

protected:

private:
	int current_state;
	int next_state;
	int size;
	double transition_matrix[5][5] = { 
		{0.7, 0.1, 0.1, 0.1, 0.0}, 
		{0.8, 0.2, 0.0, 0.0, 0.0}, 
		{0.8, 0.0, 0.2, 0.0, 0.0},
		{0.8, 0.0, 0.0, 0.0, 0.2},
		{0.8, 0.0, 0.0, 0.0, 0.2}
	};
};
