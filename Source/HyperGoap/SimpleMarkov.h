// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HYPERGOAP_API SimpleMarkov
{
public:
	SimpleMarkov();
	~SimpleMarkov();

	UFUNCTION(BlueprintCallable, Category = "SimpleMarkov")
	void SampleRun();
};
