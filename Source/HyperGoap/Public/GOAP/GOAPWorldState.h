// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>

/**
 * 
 */
class HYPERGOAP_API GOAPWorldState
{
private:
	std::map<FString, bool> states;

public:
	GOAPWorldState();

	~GOAPWorldState();

	GOAPWorldState(const std::map<FString, bool>& states);

	bool operator==(GOAPWorldState w);

	bool isIncluded(GOAPWorldState w);

	const std::map<FString, bool>& getStates();

	void setStates(const std::map<FString, bool>& states);

	void addState(FString name, bool value);

	void cleanStates();

	void joinWorldState(GOAPWorldState w);

	bool isEmpty();
};
