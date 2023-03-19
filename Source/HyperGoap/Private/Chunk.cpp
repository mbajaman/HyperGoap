// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunk.h"
#include "Enums.h"
#include "FastNoiseLite.h"
#include "ProceduralMeshComponent.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	Noise = new FastNoiseLite();

	// The Noise parameters can be tweaked and exposed as UPROPERTY to get different results
	Noise->SetFrequency(0.012f);
	Noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	Noise->SetFractalType(FastNoiseLite::FractalType_FBm);

	// Re-size blocks array. 
	Blocks.SetNum(Size * Size * Size);

	// This can also be a UPROPERTY
	Mesh->SetCastShadow(true);

}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();

	GenerateBlocks();

	GenerateMesh();

	ApplyMesh();	
}

void AChunk::GenerateBlocks()
{
	const auto Location = GetActorLocation();

	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			// x, y needs to scaled by 100 due to Unreals default measurement size
			const float Xpos = (x * 100 + Location.X) / 100;
			const float Ypos = (y * 100 + Location.Y) / 100;

			// Get Noise returns a value between -1 and 1. We add +1 so its between 0-2. 
			// Then we multiply by Size/2 to get a value between 0 and Size.
			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, Ypos) + 1) * Size / 2), 0, Size);
			
			// Blocks till Height are stone and the rest are air
			for (int z = 0; z < Height; z++)
			{
				Blocks[GetBlockIndex(x, y, z)] = EBlock::Stone;
			}

			for (int z = Height; z < Size; z++)
			{
				Blocks[GetBlockIndex(x, y, z)] = EBlock::Air;
			}
		}
	}
}

void AChunk::GenerateMesh()
{
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			for (int z = 0; z < Size; z++)
			{
				if (Blocks[GetBlockIndex(x, y, z)] != EBlock::Air)
				{
					const auto Position = FVector(x, y, z);

					for (auto Direction : { EDirection::Forward, EDirection::Right, EDirection::Back, EDirection::Left, EDirection::Up, EDirection::Down })
					{
						if (Check(GetPositionInDirection(Direction, Position)))
						{
							CreateFace(Direction, Position * 100);
						}
					}
				}
			}
		}
	}
}

void AChunk::ApplyMesh() const
{
	Mesh->CreateMeshSection(0, VertexData, TriangleData, TArray<FVector>(), UVData, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}

bool AChunk::Check(FVector Position) const
{
	// If position is out of bounds of the chunk return true. i.e., draw faces.
	if (Position.X >= Size || Position.Y >= Size || Position.Z >= Size ||
		Position.X < 0 || Position.Y < 0 || Position.Z < 0)
	{
		return true;
	}

	// Otherwise check if the block at that position is an air block or not. If it is, return true and draw face. 
	// If its not an air block, there's something solid there and we don't need to draw a face.
	return Blocks[GetBlockIndex(Position.X, Position.Y, Position.Z)] == EBlock::Air;
}

void AChunk::CreateFace(EDirection Direction, FVector Position)
{
	VertexData.Append(GetFaceVertices(Direction, Position));
	// UVData will change when adding textures
	UVData.Append({
		FVector2D(1, 1), 
		FVector2D(1, 0), 
		FVector2D(0, 0), 
		FVector2D(0, 1) 
	});
	TriangleData.Append({
		VertexCount + 3,
		VertexCount + 2,
		VertexCount,
		VertexCount + 2,
		VertexCount + 1,
		VertexCount
	});
	VertexCount += 4;
}

TArray<FVector> AChunk::GetFaceVertices(EDirection Direction, FVector Position) const
{
	TArray<FVector> Vertices;

	for (int i = 0; i < 4; i++)
	{
		// This grabs the correct cube vertices based on Direction enum by getting the vertex data from the triangle data
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] * Scale + Position);
	}
	return Vertices;
}

FVector AChunk::GetPositionInDirection(EDirection Direction, FVector Position) const
{
	// Based on direction, add that directions unit vector to the position
	switch (Direction)
	{
		case EDirection::Forward:
			return Position + FVector::ForwardVector;
		case EDirection::Right:
			return Position + FVector::RightVector;
		case EDirection::Back:
			return Position + FVector::BackwardVector;
		case EDirection::Left:
			return Position + FVector::LeftVector;
		case EDirection::Up:
			return Position + FVector::UpVector;
		case EDirection::Down:
			return Position + FVector::DownVector;
		default: throw std::invalid_argument("Invalid Direction");
	}
}

int AChunk::GetBlockIndex(int X, int Y, int Z) const
{
	// Flatenning a 3D index to 1D. You move along the Z axis first, then Y and then X.
	// X Dimension filled, then Y Dimension filled, then Z.
	return Z * Size * Size + Y * Size + X;
}
