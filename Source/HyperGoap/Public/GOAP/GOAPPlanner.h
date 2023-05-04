// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPWorldState.h"
#include "GOAPAction.h"
#include "GOAPNode.h"

/**
 * Planner uses A* serach algorithm, to find the best path to the goal state.
 */
class HYPERGOAP_API GOAPPlanner
{
private:
	GOAPWorldState* currentWorldState;

	GOAPWorldState* goalWorldState;

	TArray<UGOAPAction*> availableActions;

	TArray<GOAPNode> openList;

	TArray<GOAPNode> closedList;

	int maxDepth;

	GOAPWorldState* lastWorld = nullptr;

	TArray<UGOAPAction*> lastPlan;

public:
	GOAPPlanner();

	~GOAPPlanner();

	GOAPPlanner(GOAPWorldState* cState, GOAPWorldState* gState, const TArray<UGOAPAction*>& actions);

	GOAPNode lowestFinList(const TArray<GOAPNode>& opList);

	TArray<GOAPNode> getAdjacent(GOAPNode current, const TArray<UGOAPAction*>& vActions, APawn* pawn);

	//A* search algorithm
	TArray<UGOAPAction*> generatePlan(APawn* pawn);

	void addAction(UGOAPAction* a);

	// GETS

	GOAPWorldState getCurrentWorld();

	GOAPWorldState getGoal();

	int getMaxDepth();

	// SETS

	void SetCurrentWorld(GOAPWorldState* cState);

	void setGoal(GOAPWorldState* gState);

	void setMaxDepth(int depth);
};
