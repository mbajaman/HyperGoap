// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPWorldState.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"
#include "GOAPAction.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FState 
{
	GENERATED_USTRUCT_BODY()

		// Name of the state (predicate)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		FString name;
	
	// Value of the state (truth value)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		bool value;
};

/**
 * 
 */
UCLASS(Blueprintable)
class HYPERGOAP_API UGOAPAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		FString name;

	// Cost of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		float cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		TSubclassOf<AActor> targetsType;

	// Pre-requisites need for the action to be executed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		TArray<FState> preconditions;

	// Effects of the action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
		TArray<FState> effects;

private:

	AActor* target;
	GOAPWorldState wsPreconditions; // world state preconditions
	GOAPWorldState wsEffects; // world state effects

public:

	UGOAPAction();

	//Search all actors of targetsType in the world and return a list of them
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		TArray<AActor*> getTargetsList(APawn* pawn);

	// Function to check if it's possible to perform the action
	UFUNCTION(BlueprintImplementableEvent, Category = GOAPAction)
		bool checkProceduralPrecondition(APawn* pawn);

	// Perform the action
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = GOAPAction)
		bool performAction(APawn* pawn);

	// Generate the action's preconditions and effects
	void create_Precon_Effects();


	// COMPARATORS
	bool operator==(UGOAPAction& action);

	bool operator!=(UGOAPAction& action);

	// GETS

	// Gets the name of the action
	FString getName();

	// Gets the cost of the action
	float getCost();

	// Gets the chosen target from the targetliust or the one specific in setTarget()
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		AActor* getTarget();

	GOAPWorldState getPreconditions();

	GOAPWorldState getEffects();

	// SETS
	// Sets the name for the action
	void setName(FString n);

	// Sets the cost for the action
	void setCost(float c);

	// Sets a specific target
	UFUNCTION(BlueprintCallable, Category = GOAPAction)
		void setTarget(AActor* t);

	void setPreconditions(GOAPWorldState preconditionStates);

	void setEffects(GOAPWorldState effectStates);
};
