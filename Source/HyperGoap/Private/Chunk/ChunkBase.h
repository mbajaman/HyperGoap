// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Utils/Enums.h"
#include "Utils/ChunkMeshData.h"

#include "ChunkBase.generated.h"

class FastNoiseLite;
class UProceduralMeshComponent;

UCLASS(ABSTRACT)
class AChunkBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkBase();

	// Exposes to Unreal Editor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Chunk")
		int Size = 32; // Size of the chunk in X, Y and Z directions

	// TObjectPtr adds more safety and checks instead of typical C++ pointers
	TObjectPtr<UMaterialInterface> Material;
	float Frequency;
	EBlock State;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	* @brief Generates our Block array based on the height map from our Noise library
	*/
	virtual void Setup(const EBlock CState) PURE_VIRTUAL(AChunkBase::Setup);
	virtual void Generate2DHeightMap(const FVector Position) PURE_VIRTUAL(AChunkBase::Generate2DHeightMap);

	/*
	* @brief Populate our VertexData, TriangleData and UVData arrays and create Mesh
	*/
	virtual void GenerateMesh() PURE_VIRTUAL(AChunkBase::GenerateMesh);

	// TObjectPtr adds more safety and checks instead of typical C++ pointers
	TObjectPtr<UProceduralMeshComponent> Mesh;
	FastNoiseLite* Noise;
	FChunkMeshData MeshData;
	int VertexCount = 0;

private:	

	/*
	* @brief Will take vertex and index data and pass it to ProceduralMeshComponent. Rendering happens here
	*/
	void ApplyMesh() const;

	void GenerateHeightMap();

	void ClearMesh();

public:
	virtual TArray<EBlock> GetBlocksArray() const PURE_VIRTUAL
	(
		AChunkBase::GetBlocksArray,

		TArray<EBlock> EmptyArray;
		EmptyArray.Init(EBlock::Null, 5);
		return EmptyArray;
	);

	virtual int GetBlocksArrayIndex(int X, int Y, int Z) const PURE_VIRTUAL(AChunkBase::GetBlocksArrayIndex, return 0;);
};
