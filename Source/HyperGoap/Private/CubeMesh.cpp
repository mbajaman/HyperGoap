// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeMesh.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACubeMesh::ACubeMesh()
{
	// Create a static mesh component
	UStaticMeshComponent* cubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// Load the cube mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'")).Object;
	//UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Megascans/3D_Plants/Leptadenia_xdkgfgtqx/S_Leptadenia_xdkgfgtqx_Var2_lod3'")).Object;

	
	// Set the component's mesh
	cubeMeshComponent->SetStaticMesh(cubeMesh);

	// Set as root component
	RootComponent = cubeMeshComponent;

	RootComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
}

