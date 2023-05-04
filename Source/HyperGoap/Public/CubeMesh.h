// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "CubeMesh.generated.h"

UCLASS()
class HYPERGOAP_API ACubeMesh : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeMesh();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	

};
