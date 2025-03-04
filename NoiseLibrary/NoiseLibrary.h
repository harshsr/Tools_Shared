// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NoiseLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOOLSCOLLECTION_API UNoiseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	//Perlin Noise

	//1D
	
	//Simple Perlin Noise 1D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float SimplePerlinNoise1D(float SampleX, float Scale);

	// Perlin Noise 1D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float PerlinNoise1D(float SampleX, float Scale, float CellSize, float Blur, int32 Seed);

	//2D
	
	//Simple Perlin Noise 2D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float SimplePerlinNoise2D(float SampleX, float SampleY, float Scale);

	// Perlin Noise 2D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float PerlinNoise2D(float SampleX, float SampleY, float Scale, float CellSize, float Blur, int32 Seed);

	//3D
	
	//Simple Perlin Noise 3D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float SimplePerlinNoise3D(float SampleX, float SampleY, float Z, float Scale);

	//Perlin Noise 3D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float PerlinNoise3D(float SampleX, float SampleY, float SampleZ, float Scale, float CellSize, float Blur, int32 Seed);

	//4D
	
	//Simple Perlin Noise 4D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float SimplePerlinNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float Scale);

	//Perlin Noise 4D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Perlin Noise")
	static float PerlinNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float Scale, float CellSize, float Blur, int32 Seed);


	//Worley Noise

	// Worley Noise 1D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Worley Noise")
	static float WorleyNoise1D(float SampleX, int Seed, float CellSize, float Blur);

	// Worley Noise 2D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Worley Noise")
	static float WorleyNoise2D(float SampleX, float SampleY, int Seed, float CellSize, float Blur);

	// Worley Noise 3D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Worley Noise")
	static float WorleyNoise3D(float SampleX, float SampleY, float SampleZ, int Seed, float CellSize, float Blur);

	// Worley Noise 4D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Worley Noise")
	static float WorleyNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, int Seed, float CellSize, float Blur);



	//Voronoi Noise

	//Voronoi Noise 2D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Voronoi Noise")
	static float VoronoiNoise2D(float SampleX, float SampleY, float CellSize, int Seed, float Blur);

	//Voronoi Noise 3D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Voronoi Noise")
	static float VoronoiNoise3D(float SampleX, float SampleY, float SampleZ, float CellSize, int Seed, float Blur);

	//Voronoi Noise 4D
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Voronoi Noise")
	static float VoronoiNoise4D(float SampleX, float SampleY, float SampleZ, float SampleW, float CellSize, int Seed, float Blur);
};
