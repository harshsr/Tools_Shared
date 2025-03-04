// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseLibrary/NoiseLibrary.h"


float UNoiseLibrary::SimplePerlinNoise1D(float SampleX, float Scale)
{
    if (Scale <= 0.f)
    {
        Scale = 0.01f; 
    }
    
    float AdjustedX = SampleX / Scale;
    float NoiseValue = FMath::PerlinNoise2D(FVector2D(AdjustedX, 0.0f));
    return NoiseValue;
}

float UNoiseLibrary::PerlinNoise1D(float SampleX, float Scale, float CellSize, float Blur, int32 Seed)
{
    if (Scale <= 0.f) Scale = 0.01f;
    if (CellSize <= 0.f) CellSize = 0.01f;
    if (SampleX == 0.f) SampleX = 0.01f;

    FRandomStream RandomStream(Seed);
    float OffsetX = RandomStream.FRandRange(-100000.f, 100000.f);

    float AdjustedX = ((SampleX / CellSize) / Scale) + OffsetX;

    float NoiseValue = FMath::PerlinNoise2D(FVector2D(AdjustedX, 1.0f)) * 2;

    float Distance = FMath::Sqrt(SampleX * SampleX); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return NoiseValue;
}


float UNoiseLibrary::SimplePerlinNoise2D(float SampleX, float SampleY, float Scale)
{
   
    if (Scale <= 0.f)
    {
        Scale = 1.0f; 
    }


    
    float AdjustedX = SampleX / Scale;
    float AdjustedY = SampleY / Scale;

  
    float NoiseValue = (FMath::PerlinNoise2D(FVector2D(AdjustedX, AdjustedY)));

    return NoiseValue;
}


float UNoiseLibrary::PerlinNoise2D(float SampleX, float SampleY, float Scale, float CellSize, float Blur, int32 Seed)
{
   
    if (Scale <= 0.f) Scale = 0.01f;
    if (CellSize <= 0.f) CellSize = 0.01f;
    if (SampleX == 0.f) SampleX = 0.01f;
    if (SampleY == 0.f) SampleY = 0.01f;
    if (Blur == 0.f) Blur = 0.01f;

    
    FRandomStream RandomStream(Seed);
    float OffsetX = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetY = RandomStream.FRandRange(-100000.f, 100000.f);

    
    float AdjustedX = ((SampleX / CellSize) / Scale) + OffsetX;
    float AdjustedY = ((SampleY / CellSize) / Scale) + OffsetY;

    
    float NoiseValue = FMath::PerlinNoise2D(FVector2D(AdjustedX, AdjustedY));

   
    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance/Blur));

  
    NoiseValue *= AttenuatedAmplitude;

    return NoiseValue;
}


float UNoiseLibrary::SimplePerlinNoise3D(float SampleX, float SampleY, float Z, float Scale)
{
   
    if (Scale <= 0.f)
    {
        Scale = 0.01f; 
    }

   
    float AdjustedX = SampleX / Scale;
    float AdjustedY = SampleY / Scale;
    float AdjustedZ = Z / Scale;

  
    float NoiseValue = FMath::PerlinNoise3D(FVector(AdjustedX, AdjustedY, AdjustedZ));

    return NoiseValue;
}

float UNoiseLibrary::PerlinNoise3D(float SampleX, float SampleY, float SampleZ, float Scale, float CellSize, float Blur, int32 Seed)
{
  
    if (Scale <= 0.f) Scale = 0.01f;
    if (CellSize <= 0.f) CellSize = 0.01f;
    if (SampleX == 0.f) SampleX = 0.01f;

    FRandomStream RandomStream(Seed);
    float OffsetX = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetY = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetZ = RandomStream.FRandRange(-100000.f, 100000.f);

    float AdjustedX = ((SampleX / CellSize) / Scale) + OffsetX;
    float AdjustedY = ((SampleY / CellSize) / Scale) + OffsetY;
    float AdjustedZ = ((SampleZ / CellSize) / Scale) + OffsetZ;

    float NoiseValue = FMath::PerlinNoise3D(FVector(AdjustedX, AdjustedY, AdjustedZ));

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return NoiseValue;
}

float UNoiseLibrary::SimplePerlinNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float Scale)
{
    if (Scale <= 0.f)
    {
        Scale = 0.01f;
    }

    float AdjustedX = SampleX / Scale;
    float AdjustedY = SampleY / Scale;
    float AdjustedZ = SampleZ / Scale;
    float AdjustedW = SampleW / Scale;

    float NoiseValue1 = FMath::PerlinNoise3D(FVector(AdjustedX, AdjustedY, AdjustedZ));
    float NoiseValue2 = FMath::PerlinNoise3D(FVector(AdjustedX + AdjustedW, AdjustedY + AdjustedW, AdjustedZ + AdjustedW));

    float NoiseValue = (NoiseValue1 + NoiseValue2);

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::PerlinNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float Scale, float CellSize, float Blur, int32 Seed)
{
    if (Scale <= 0.f) Scale = 0.01f;
    if (CellSize <= 0.f) CellSize = 0.01f;
    if (SampleX == 0.f) SampleX = 0.01f;

    FRandomStream RandomStream(Seed);
    float OffsetX = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetY = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetZ = RandomStream.FRandRange(-100000.f, 100000.f);
    float OffsetW = RandomStream.FRandRange(-100000.f, 100000.f);

    float AdjustedX = ((SampleX / CellSize) / Scale) + OffsetX;
    float AdjustedY = ((SampleY / CellSize) / Scale) + OffsetY;
    float AdjustedZ = ((SampleZ / CellSize) / Scale) + OffsetZ;
    float AdjustedW = ((SampleW / CellSize) / Scale) + OffsetW;

    float NoiseValue1 = FMath::PerlinNoise3D(FVector(AdjustedX, AdjustedY, AdjustedZ));
    float NoiseValue2 = FMath::PerlinNoise3D(FVector(AdjustedX + AdjustedW, AdjustedY + AdjustedW, AdjustedZ + AdjustedW));

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ + SampleW * SampleW); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    float NoiseValue = (NoiseValue1 + NoiseValue2) * AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}


float UNoiseLibrary::WorleyNoise1D(float SampleX, int Seed, float CellSize, float Blur)
{
    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;
    
    int CellX = FMath::FloorToInt(SampleX / CellSize);

    for (int offsetX = -1; offsetX <= 1; offsetX++)
    {
        int CellSeed = (CellX + offsetX) * 73856093 ^ Seed;
        RandomStream.Initialize(CellSeed);

        float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;

        float Distance = FMath::Abs(PointX - SampleX);
        MinDistance = FMath::Min(MinDistance, Distance);
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::WorleyNoise2D(float SampleX, float SampleY, int Seed, float CellSize, float Blur)
{
    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);

    for (int offsetY = -1; offsetY <= 1; offsetY++)
    {
        for (int offsetX = -1; offsetX <= 1; offsetX++)
        {
            int CellSeed = (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663 ^ Seed;
            RandomStream.Initialize(CellSeed);

            float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
            float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;

            float Distance = FMath::Sqrt(FMath::Pow(PointX - SampleX, 2) + FMath::Pow(PointY - SampleY, 2));
            MinDistance = FMath::Min(MinDistance, Distance);
        }
    }

    float NoiseValue = ((MinDistance / CellSize)*2)-1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::WorleyNoise3D(float SampleX, float SampleY, float SampleZ, int Seed, float CellSize, float Blur)
{
    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);
    int CellZ = FMath::FloorToInt(SampleZ / CellSize);

    for (int offsetZ = -1; offsetZ <= 1; offsetZ++)
    {
        for (int offsetY = -1; offsetY <= 1; offsetY++)
        {
            for (int offsetX = -1; offsetX <= 1; offsetX++)
            {
                int CellSeed = (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663 ^ (CellZ + offsetZ) * 83492791 ^ Seed;
                RandomStream.Initialize(CellSeed);

                float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
                float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;
                float PointZ = (CellZ + offsetZ) * CellSize + RandomStream.FRand() * CellSize;

                float Distance = FMath::Sqrt(FMath::Pow(PointX - SampleX, 2) + FMath::Pow(PointY - SampleY, 2) + FMath::Pow(PointZ - SampleZ, 2));
                MinDistance = FMath::Min(MinDistance, Distance);
            }
        }
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::WorleyNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, int Seed, float CellSize, float Blur)
{
    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);
    int CellZ = FMath::FloorToInt(SampleZ / CellSize);
    int CellW = FMath::FloorToInt(SampleW / CellSize);

    for (int offsetW = -1; offsetW <= 1; offsetW++)
    {
        for (int offsetZ = -1; offsetZ <= 1; offsetZ++)
        {
            for (int offsetY = -1; offsetY <= 1; offsetY++)
            {
                for (int offsetX = -1; offsetX <= 1; offsetX++)
                {
                    int CellSeed = (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663 ^ (CellZ + offsetZ) * 83492791 ^ (CellW + offsetW) * 286293355 ^ Seed;
                    RandomStream.Initialize(CellSeed);

                    float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
                    float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;
                    float PointZ = (CellZ + offsetZ) * CellSize + RandomStream.FRand() * CellSize;
                    float PointW = (CellW + offsetW) * CellSize + RandomStream.FRand() * CellSize;

                    float Distance = FMath::Sqrt(FMath::Pow(PointX - SampleX, 2) + FMath::Pow(PointY - SampleY, 2) + FMath::Pow(PointZ - SampleZ, 2) + FMath::Pow(PointW - SampleW, 2));
                    MinDistance = FMath::Min(MinDistance, Distance);
                }
            }
        }
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ + SampleW * SampleW);
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}


float UNoiseLibrary::VoronoiNoise2D(float SampleX, float SampleY, float CellSize, int Seed, float Blur)
{
    if (CellSize <= 0.0f)
    {
        CellSize = 1.0f;
    }
    if (Blur <= 0.0f)
    {
        Blur = 1.0f;
    }

    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);

    for (int offsetY = -1; offsetY <= 1; offsetY++)
    {
        for (int offsetX = -1; offsetX <= 1; offsetX++)
        {
            RandomStream.Initialize(Seed + (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663);

            float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
            float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;

            float Distance = FVector2D::Distance(FVector2D(SampleX, SampleY), FVector2D(PointX, PointY));

            MinDistance = FMath::Min(MinDistance, Distance);
        }
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::VoronoiNoise3D(float SampleX, float SampleY, float SampleZ, float CellSize, int Seed, float Blur)
{
    if (CellSize <= 0.0f) CellSize = 1.0f;
    if (Blur <= 0.0f) Blur = 1.0f;

    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);
    int CellZ = FMath::FloorToInt(SampleZ / CellSize);

    for (int offsetZ = -1; offsetZ <= 1; offsetZ++)
    {
        for (int offsetY = -1; offsetY <= 1; offsetY++)
        {
            for (int offsetX = -1; offsetX <= 1; offsetX++)
            {
                RandomStream.Initialize(Seed + (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663 ^ (CellZ + offsetZ) * 83492791);

                float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
                float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;
                float PointZ = (CellZ + offsetZ) * CellSize + RandomStream.FRand() * CellSize;

                float Distance = FVector::Dist(FVector(SampleX, SampleY, SampleZ), FVector(PointX, PointY, PointZ));

                MinDistance = FMath::Min(MinDistance, Distance);
            }
        }
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}

float UNoiseLibrary::VoronoiNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float CellSize, int Seed, float Blur)
{
    if (CellSize <= 0.0f) CellSize = 1.0f;
    if (Blur <= 0.0f) Blur = 1.0f;

    FRandomStream RandomStream(Seed);
    float MinDistance = MAX_flt;

    int CellX = FMath::FloorToInt(SampleX / CellSize);
    int CellY = FMath::FloorToInt(SampleY / CellSize);
    int CellZ = FMath::FloorToInt(SampleZ / CellSize);
    int CellW = FMath::FloorToInt(SampleW / CellSize);

    for (int offsetW = -1; offsetW <= 1; offsetW++)
    {
        for (int offsetZ = -1; offsetZ <= 1; offsetZ++)
        {
            for (int offsetY = -1; offsetY <= 1; offsetY++)
            {
                for (int offsetX = -1; offsetX <= 1; offsetX++)
                {
                    RandomStream.Initialize(Seed + (CellX + offsetX) * 73856093 ^ (CellY + offsetY) * 19349663 ^ (CellZ + offsetZ) * 83492791 ^ (CellW + offsetW) * 286293355);

                    float PointX = (CellX + offsetX) * CellSize + RandomStream.FRand() * CellSize;
                    float PointY = (CellY + offsetY) * CellSize + RandomStream.FRand() * CellSize;
                    float PointZ = (CellZ + offsetZ) * CellSize + RandomStream.FRand() * CellSize;
                    float PointW = (CellW + offsetW) * CellSize + RandomStream.FRand() * CellSize;

                    float Distance = FMath::Sqrt(FMath::Pow(PointX - SampleX, 2) + FMath::Pow(PointY - SampleY, 2) + FMath::Pow(PointZ - SampleZ, 2) + FMath::Pow(PointW - SampleW, 2));

                    MinDistance = FMath::Min(MinDistance, Distance);
                }
            }
        }
    }

    float NoiseValue = ((MinDistance / CellSize) * 2) - 1;

    float Distance = FMath::Sqrt(SampleX * SampleX + SampleY * SampleY + SampleZ * SampleZ + SampleW * SampleW); 
    float AttenuatedAmplitude = (1.0f - FMath::Exp(-Distance / Blur));

    NoiseValue *= AttenuatedAmplitude;

    return FMath::Clamp(NoiseValue, -1.0f, 1.0f);
}


