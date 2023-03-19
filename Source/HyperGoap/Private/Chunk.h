// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.generated.h"

// Forward Declarations
enum class EBlock;
enum class EDirection;
class FastNoiseLite;
class UProceduralMeshComponent;

UCLASS()
class AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	// Exposes to Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Chunk")
		int Size = 32; // Size of the chunk in X, Y and Z directions

	// Exposes to Unreal Editor
	UPROPERTY(EditAnywhere, Category = "Chunk")
		int Scale = 1; // Scale represents the scale of the faces drawn in the chunk

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	// TObjectPtr adds more safety and checks instead of typical C++ pointers
	TObjectPtr<UProceduralMeshComponent> Mesh;
	TObjectPtr<FastNoiseLite> Noise;

	// 1D-Array of blocks for the current chunk
	TArray<EBlock> Blocks; 

	// Vertex, Triangle and UVData that will generated and setup for the ProceduralMeshComponent
	TArray<FVector> VertexData;
	TArray<int> TriangleData;
	TArray<FVector2D> UVData;

	// Used for generation of the above MeshComponent data
	int VertexCount = 0;

	// Vertices that correspond to 8 points of a cube
	const FVector BlockVertexData[8] = {
		FVector(100, 100, 100),
		FVector(100, 0, 100),
		FVector(100, 0, 0),
		FVector(100, 100, 0),
		FVector(0, 0, 100),
		FVector(0, 100, 100),
		FVector(0, 100, 0),
		FVector(0, 0, 0)
	};

	// 6 index positions that correspond to 6 faces of the cube.
	// ORDER MUST MATCH EDirection enum
	const int BlockTriangleData[24] = {
		0, 1, 2, 3, // Forward
		5, 0, 3, 6, // Right
		4, 5, 6, 7, // Back
		1, 4, 7, 2, // Left
		5, 4, 1, 0, // Up
		3, 2, 7, 6  // Down
	};

	/*
	* @brief Generates our Block array based on the height map from our Noise library
	*/
	void GenerateBlocks();

	/*
	* @brief Populate our VertexData, TriangleData and UVData arrays and create Mesh
	*/
	void GenerateMesh();

	/*
	* @brief Will take vertex and index data and pass it to ProceduralMeshComponent. Rendering happens here
	*/
	void ApplyMesh() const;

	/*
	* @brief UTILITY METHOD used to check if a given position contains an opaque block or a transparent block
	*/
	bool Check(FVector Position) const;

	/*
	* Creates faces to our mesh given some direction and position data
	*/
	void CreateFace(EDirection Direction, FVector Position);

	/*
	* @brief UTILITY METHOD used to query the vertex lookup table.
	* Given a direction and position, it will return the 4 vertices that correspond to that face
	*/
	TArray<FVector> GetFaceVertices(EDirection Direction, FVector Position) const;

	/*
	* @brief UTILITY METHOD Given a position and direction, it will return an adjacent position in that direction
	* Adding a direction vector to position
	*/
	FVector GetPositionInDirection(EDirection Direction, FVector Position) const;

	/*
	* @brief We are storing our blocks in a 1D array but blocks will be represented in 3D.
	* To flatten out X,Y and Z coordinates into a single index. It will return the correct array index for that block in the Blocks array.
	*/
	int GetBlockIndex(int X, int Y, int Z) const;
};
