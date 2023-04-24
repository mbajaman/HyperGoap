// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunk.h"
#include "Utils/FastNoiseLite.h"
#include "CubeMesh.h"

void AChunk::Setup(EBlock CState)
{
	Blocks.SetNum(Size * Size * Size);
	ChunkState = CState;
}

void AChunk::Generate2DHeightMap(const FVector Position)
{
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			const float Xpos = x + Position.X;
			const float Ypos = y + Position.Y;

			// Get Noise returns a value between -1 and 1. We add +1 so its between 0-2. 
			// Then we multiply by Size/2 to get a value between 0 and Size.
			const int Height = FMath::Clamp(FMath::RoundToInt((Noise->GetNoise(Xpos, Ypos) + 1) * Size / 2), 0, Size);

			// Blocks till Height are stone and the rest are air
			// TODO: Change Block type based on next state
			for (int z = 0; z < Height; z++)
			{
				Blocks[GetBlockIndex(x, y, z)] = ChunkState;
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

bool AChunk::Check(FVector Position) const
{
	// If position is out of bounds of the chunk return true. i.e., draw faces.
	if (Position.X >= Size || Position.Y >= Size || Position.X < 0 || Position.Y < 0 || Position.Z < 0) return true;
	if (Position.Z >= Size) return true;

	// Otherwise check if the block at that position is an air block or not. If it is, return true and draw face. 
	// If its not an air block, there's something solid there and we don't need to draw a face.
	return Blocks[GetBlockIndex(Position.X, Position.Y, Position.Z)] == EBlock::Air;
}

TArray<FVector> AChunk::GetFaceVertices(EDirection Direction, FVector Position) const
{
	TArray<FVector> Vertices;

	for (int i = 0; i < 4; i++)
	{
		// This grabs the correct cube vertices based on Direction enum by getting the vertex data from the triangle data
		Vertices.Add(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] + Position);
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

FVector AChunk::GetNormal(const EDirection Direction) const
{
	switch (Direction)
	{
	case EDirection::Forward:
		return FVector::ForwardVector;
	case EDirection::Right:
		return FVector::RightVector;
	case EDirection::Back:
		return FVector::BackwardVector;
	case EDirection::Left:
		return FVector::LeftVector;
	case EDirection::Up:
		return FVector::UpVector;
	case EDirection::Down:
		return FVector::DownVector;
	default: throw std::invalid_argument("Invalid Direction");
	}
}

void AChunk::CreateFace(EDirection Direction, FVector Position)
{
	//const auto Color = FColor::MakeRandomColor();
	const auto Normal = GetNormal(Direction);
	FColor Color;
	switch (ChunkState) {
		case EBlock::Dirt:
			Color = FColor(0, 0, 0, GetTextureIndex(ChunkState,Normal));
			break;
		case EBlock::Stone:
			Color = FColor(0, 0, 0, GetTextureIndex(ChunkState, Normal));
			break;
		case EBlock::Grass:
			Color = FColor(0, 0, 0, GetTextureIndex(ChunkState, Normal));
			break;
		default:
			Color = FColor::MakeRandomColor();
	}

	MeshData.Vertices.Append(GetFaceVertices(Direction, Position));

	MeshData.Triangles.Append({ 
		VertexCount + 3,
		VertexCount + 2,
		VertexCount,
		VertexCount + 2,
		VertexCount + 1,
		VertexCount 
	});

	MeshData.Normals.Append({ 
		Normal, 
		Normal, 
		Normal, 
		Normal 
	});

	MeshData.Colors.Append({ 
		Color, 
		Color, 
		Color, 
		Color 
	});

	MeshData.UV0.Append({
		FVector2D(1, 1), 
		FVector2D(1, 0), 
		FVector2D(0, 0), 
		FVector2D(0, 1) 
	});
	VertexCount += 4;
}

int AChunk::GetBlockIndex(int X, int Y, int Z) const
{
	// Flatenning a 3D index to 1D. You move along the Z axis first, then Y and then X.
	// X Dimension filled, then Y Dimension filled, then Z.
	return Z * Size * Size + Y * Size + X;
}

TArray<EBlock> AChunk::GetBlocksArray() const
{
	// Log size of Blocks array
	return Blocks;
}

int AChunk::GetBlocksArrayIndex(int X, int Y, int Z) const
{
	return GetBlockIndex(X, Y, Z);
}

int AChunk::GetTextureIndex(EBlock Block, FVector Normal) const
{
	switch (Block)
	{
		case EBlock::Grass:
			return 0;
		case EBlock::Dirt:
			return 1;
		case EBlock::Stone:
			return 2;
		default:
			return 255;
	}

}
