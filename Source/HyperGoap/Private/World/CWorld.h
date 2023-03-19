// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Utils/Enums.h"
#include "Utils/MarkovChain.h"

#include "CWorld.generated.h"

class AChunkBase;

UCLASS()
class ACWorld final: public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWorld();

	UPROPERTY(EditInstanceOnly, Category="World")
		TSubclassOf<AChunkBase> Chunk;

	UPROPERTY(EditInstanceOnly, Category = "World")
		int DrawDistance = 5;

	UPROPERTY(EditInstanceOnly, Category = "World")
		TObjectPtr<UMaterialInterface> Material;

	UPROPERTY(EditAnywhere, Category = "World")
		int Size = 32;

	UPROPERTY(EditInstanceOnly, Category = "World")
		float Frequency = 0.01f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int ChunkCount;

	void Generate2DWorld();

	AMarkovChain* MarkovChain;

};
