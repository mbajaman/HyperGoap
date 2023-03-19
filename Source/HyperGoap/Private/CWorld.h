// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWorld.generated.h"

UCLASS()
class ACWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWorld();

	UPROPERTY(EditAnywhere, Category="CWorld")
		TSubclassOf<AActor> Chunk;

	UPROPERTY(EditAnywhere, Category = "CWorld")
		int DrawDistance = 5;

	UPROPERTY(EditAnywhere, Category = "CWorld")
		int ChunkSize = 32;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
