// Fill out your copyright notice in the Description page of Project Settings.


#include "CWorld.h"
#include "Utils/MarkovChain.h"
#include "Chunk/ChunkBase.h"
#include "CubeMesh.h"


// Sets default values
ACWorld::ACWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	mChain = new MarkovChain();
}

// Called when the game starts or when spawned
void ACWorld::BeginPlay()
{
	Super::BeginPlay();

	Generate2DWorld();

	UE_LOG(LogTemp, Warning, TEXT("%d Chunks Created"), ChunkCount);
}

void ACWorld::Generate2DWorld()
{
	mChain->GenerateStatesArray();
	TArray<int> StatesArray;
	StatesArray.Append(mChain->GetStates());
	UE_LOG(LogTemp, Warning, TEXT("Array Size: %d"), StatesArray.Num());

	for (auto& state : StatesArray)
	{
		//state += 2;
		UE_LOG(LogTemp, Warning, TEXT("State: %d"), state);
	}

	int transition = 0;

	for (int x = -DrawDistance; x <= DrawDistance; x++)
	{
		for (int y = -DrawDistance; y <= DrawDistance; y++)
		{
			auto transform = FTransform(
				FRotator::ZeroRotator,
				FVector(x * Size * 100, y * Size * 100, 0),
				FVector::OneVector
			);

			const auto chunk = GetWorld()->SpawnActorDeferred<AChunkBase>(Chunk, transform, this);
			chunk->Frequency = Frequency;
			chunk->Material = Material;
			chunk->Size = Size;

			if (transition < StatesArray.Num())
			{
				switch (StatesArray[transition])
				{
				case 0:
					chunk->State = EBlock::Grassland;
					chunk->Type = States::Grassland;
					break;
				case 1:
					chunk->State = EBlock::Village;
					chunk->Type = States::Village;
					break;
				case 2:
					chunk->State = EBlock::AbandonedBuilding;
					chunk->Type = States::AbandonedBuilding;
					break;
				case 3:
					chunk->State = EBlock::Pond;
					chunk->Type = States::Pond;
					break;
				}
			}

			chunk->FinishSpawning(transform);

			// The below 3 lines can also be removed I think
			FVector ChunkOrigin = chunk->GetActorLocation();
			FVector ChunkSize = chunk->GetActorScale() * Size;
			TArray<EBlock> ChunkBlocks = chunk->GetBlocksArray();

			// WORKING CODE FOR GENERATING FOLIAGE PROCEDURALLY BY PLACING STATIC MESHES IN THE WORLD
			// This puts a cube in EVERY voxel in the chunk
			//for (int v = 0; v < Size; v++)
			//{
			//	for (int u = 0; u < Size; u++)
			//	{
			//		for (int w = 0; w < Size; w++)
			//		{
			//			if (ChunkBlocks[chunk->GetBlocksArrayIndex(v, u, w)] != EBlock::Air &&
			//				(w == Size - 1 || ChunkBlocks[chunk->GetBlocksArrayIndex(v, u, w + 1)] == EBlock::Air))
			//			{
			//				FVector VoxelCenter = FVector(
			//					ChunkOrigin.X + (v * 100) + 50, 
			//					ChunkOrigin.Y + (u * 100) + 50, 
			//					ChunkOrigin.Z + (w * 100) + 100
			//				);
			//				FVector VoxelTopCenter = FVector(
			//					ChunkOrigin.X + (v + 0.5f) * Size,
			//					ChunkOrigin.Y + (u + 0.5f) * Size,
			//					ChunkOrigin.Z + (w + 1) * Size
			//				);
			//				GetWorld()->SpawnActor<ACubeMesh>(VoxelCenter, FRotator::ZeroRotator);
			//			}
			//		}
			//	}
			//}

			ChunkCount++;
			transition++;
		}
	}
}


