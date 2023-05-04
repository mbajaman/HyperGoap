// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAP/GOAPWorldState.h"

GOAPWorldState::GOAPWorldState()
{
}

GOAPWorldState::~GOAPWorldState()
{
}

GOAPWorldState::GOAPWorldState(const std::map<FString, bool>& st)
{
	states = st;
}

bool GOAPWorldState::operator==(GOAPWorldState w)
{
	return false;
}

bool GOAPWorldState::isIncluded(GOAPWorldState w)
{
	for (auto requirement : w.getStates())
	{
		auto it = states.find(requirement.first);
		if (it != states.end())
		{
			if (it->second != requirement.second)
				return false;
		}
		else return false;
	}
	return true;
}

const std::map<FString, bool>& GOAPWorldState::getStates()
{
	return states;
}

void GOAPWorldState::setStates(const std::map<FString, bool>& st)
{
	states = st;
}

void GOAPWorldState::addState(FString name, bool value)
{
	states[name] = value;
}

void GOAPWorldState::cleanStates()
{
	states.clear();
}

void GOAPWorldState::joinWorldState(GOAPWorldState w)
{
	for (auto state : w.getStates())
	{
		states[state.first] = state.second;
	}
}

bool GOAPWorldState::isEmpty()
{
	return states.size() == 0;
}
