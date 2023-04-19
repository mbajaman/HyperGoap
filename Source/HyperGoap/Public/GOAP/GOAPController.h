// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPPlanner.h"
#include "AIController.h"
#include "Engine.h"
#include "GOAPController.generated.h"

/**
 * 
 */
UCLASS()
class HYPERGOAP_API AGOAPController : public AAIController
{
	GENERATED_BODY()

public:

	// State of the current world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<FState> currentWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<FState> desiredWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		TArray<TSubclassOf<UGOAPAction>> actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		int maxDepth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		bool debug = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
		bool controller;

private:
	GOAPPlanner* planner;

	TArray<UGOAPAction*> auxActions;

	TArray<UGOAPAction*> plan;

	GOAPWorldState wsCurrentWorld;

	GOAPWorldState wsDesiredWorld;


public:
	AGOAPController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* pawn) override;

	virtual void Tick(float DeltaSeconds) override;

	// Create and execute the plan
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		bool executeGOAP();

	// Creates actions plans
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		bool generatePlan();

	// Returns that actions that make up the plan
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<UGOAPAction*> getPlan();

	// Sets the goal of the agent, this funciton can be used to change the goal
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void setGoal(const TArray<FState>& newGoal);

	// Adds or modified states from the desited world state. 
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void updateGoal(const TArray<FState>& states);

	// Sets current world state of the AI, can be used to update the current world state
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void setCurrentWorld(const TArray<FState>& newCurrentWorld);

	// Adds or modifies states from the current world state.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		void updateCurrentWorld(const TArray<FState>& states);

	// Return the current world's states
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<FState> getCurrentWorldStates();

	// Returns the desired world's states
	UFUNCTION(BlueprintCallable, Category = GOAPController)
		TArray<FState> getDesiredWorldStates();

private:
	void debugInfo();
};
