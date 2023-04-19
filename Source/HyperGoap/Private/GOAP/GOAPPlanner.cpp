// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/GOAPPlanner.h"

GOAPPlanner::GOAPPlanner()
{
}

GOAPPlanner::~GOAPPlanner()
{
}

bool containsNode(GOAPNode node, const TArray<GOAPNode>& list)
{
	bool contains = false;
	for (GOAPNode n : list)
	{
		if (n == node)
		{
			contains = true;
			break;
		}
	}
	return contains;
}

GOAPPlanner::GOAPPlanner(GOAPWorldState* cState, GOAPWorldState* gState, const TArray<UGOAPAction*>& actions)
{
	currentWorldState = cState;
	goalWorldState = gState;
	availableActions = actions;
}

GOAPNode GOAPPlanner::lowestFinList(const TArray<GOAPNode>& opList)
{
	GOAPNode node;

	float minF = MAX_FLT;
	for (GOAPNode n : opList)
	{
		if ((n.getF()) < minF)
		{
			node = n;
			minF = n.getF();
		}
	}

	return node;
}

TArray<GOAPNode> GOAPPlanner::getAdjacent(GOAPNode current, const TArray<UGOAPAction*>& vActions, APawn* pawn)
{
	TArray<GOAPNode> adjNodes;
	GOAPNode adjacent;
	GOAPWorldState world;

	for (int i = 0; i < vActions.Num(); i++)
	{
		const bool bPredeconditionMet = current.getWorld().isIncluded(vActions[i]->getPreconditions());

		const bool bSameActionAsBefore = current.getAction() == vActions[i];

		const bool bProceduralPreconditionFulfilled = vActions[i]->checkProceduralPrecondition(pawn);

		if (bPredeconditionMet && !bSameActionAsBefore && bProceduralPreconditionFulfilled)
		{
			world = current.getWorld();
			world.joinWorldState(vActions[i]->getEffects());
			adjacent.setWorld(world);
			adjacent.SetAction(vActions[i]);
			adjNodes.Push(adjacent);
		}
	}
	return adjNodes;
}

TArray<UGOAPAction*> GOAPPlanner::generatePlan(APawn* pawn)
{
	TArray<UGOAPAction*> solution;

	GOAPNode start;
	start.setWorld(*currentWorldState);
	start.setParent(-1);
	GOAPNode last;
	openList.Empty();
	closedList.Empty();
	openList.Push(start);

	bool continues = true;
	bool goalReached = false;

	while (continues)
	{
		GOAPNode current = lowestFinList(openList);
		openList.Remove(current);
		closedList.Push(current);
		int pos = closedList.Num() - 1;

		// When the plan reached the goal, plan stops
		if (current.getWorld().isIncluded(*goalWorldState))
		{
			last = current;
			continues = false;
			goalReached = true;
			break;
		}

		// Get adjacent of actual node
		TArray<GOAPNode> adjacents = getAdjacent(current, availableActions, pawn);

		// Explor adjacent nodes
		for (GOAPNode& adjacent : adjacents)
		{
			if (!containsNode(adjacent, openList))
			{
				adjacent.setParent(pos);
				adjacent.setH(current.getWorld());
				adjacent.setG(current);
				openList.Push(adjacent);
			}

			// If the current path to adj node is cheaper than the previous one, the path changes
			else if (adjacent.getG() > adjacent.getG() + current.getG())
			{
				adjacent.setParent(pos);
				adjacent.setG(current);
			}
		}

		// If open list is empty or the algorithm has reached the max number of iterations, the plan stops
		if (openList.Num() == 0 || closedList.Num() > getMaxDepth())
		{
			continues = false;
		}
	}

	if (goalReached)
	{
		GOAPNode planNode = last;
		while (!(planNode == start))
		{
			solution.Push(planNode.getAction());
			planNode = closedList[planNode.getParent()];
		}
	}

	return solution;
}

void GOAPPlanner::addAction(UGOAPAction* a)
{
	this->availableActions.Push(a);
}

GOAPWorldState GOAPPlanner::getCurrentWorld()
{
	return *currentWorldState;
}

GOAPWorldState GOAPPlanner::getGoal()
{
	return *goalWorldState;
}

int GOAPPlanner::getMaxDepth()
{
	return maxDepth;
}

void GOAPPlanner::SetCurrentWorld(GOAPWorldState* w)
{
	this->currentWorldState = w;
}

void GOAPPlanner::setGoal(GOAPWorldState* g)
{
	this->goalWorldState = g;
}

void GOAPPlanner::setMaxDepth(int depth)
{
	this->maxDepth = depth;
}
