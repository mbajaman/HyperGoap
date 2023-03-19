// Fill out your copyright notice in the Description page of Project Settings.


#include "CWorld.h"

#include "Chunk/ChunkBase.h"
#include "Utils/MarkovChain.h"

// Sets default values
ACWorld::ACWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	//MarkovChain->GenerateStatesArray();
	//TArray<int> StatesArray = MarkovChain->GetStates();
	//for (int x = 0; x < MarkovChain->GetStates().Num(); x++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("State: %d"), MarkovChain->GetStates()[x] + 2);
	//}

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

			double random_number = FMath::FRandRange(0.0, 1.0);
			if (random_number < 0.5)
			{
				chunk->State = EBlock::Stone;
			}
			else
			{
				chunk->State = EBlock::Dirt;
			}

			ChunkCount++;
		}
	}
}


