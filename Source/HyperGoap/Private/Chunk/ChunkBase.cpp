// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkBase.h"

#include "Utils/FastNoiseLite.h"
#include "ProceduralMeshComponent.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AChunkBase::AChunkBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("ChunkMesh");
	Noise = new FastNoiseLite();

	Mesh->SetCastShadow(true);

	// Set Mesh as root
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AChunkBase::BeginPlay()
{
	Super::BeginPlay();

	// The Noise parameters can be tweaked and exposed as UPROPERTY to get different results
	Noise->SetFrequency(Frequency);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);

	Setup(State, Type);

	GenerateHeightMap();

	GenerateMesh();

	UE_LOG(LogTemp, Warning, TEXT("Vertex Count : %d"), VertexCount);

	ApplyMesh();
}

void AChunkBase::GenerateHeightMap()
{
	Generate2DHeightMap(GetActorLocation() / 100);
}

void AChunkBase::ApplyMesh() const
{
	Mesh->SetMaterial(0, Material);
	Mesh->CreateMeshSection(
		0,
		MeshData.Vertices,
		MeshData.Triangles,
		MeshData.Normals,
		MeshData.UV0,
		MeshData.Colors,
		TArray<FProcMeshTangent>(),
		true
	);
}

void AChunkBase::ClearMesh()
{
	VertexCount = 0;
	MeshData.Clear();
}