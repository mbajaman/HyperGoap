// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/GOAPAction.h"

UGOAPAction::UGOAPAction()
{
}

TArray<AActor*> UGOAPAction::getTargetsList(APawn* pawn)
{
	TArray<AActor*> actorsFound;
	UGameplayStatics::GetAllActorsOfClass(pawn->GetWorld(), targetsType, actorsFound);
	return actorsFound;
}

void UGOAPAction::create_Precon_Effects()
{
	for (FState itrP : preconditions)
	{
		wsPreconditions.addState(itrP.name, itrP.value);
	}
	
	for (FState itrE : effects)
	{
		wsEffects.addState(itrE.name, itrE.value);
	}

	if(targetsType == NULL)
		UE_LOG(LogTemp, Warning, TEXT("No target type specified for action %s"), *name);
}

bool UGOAPAction::operator==(UGOAPAction& action)
{
	return this->cost == action.getCost() && target == action.getTarget() &&
		wsPreconditions == action.getPreconditions() && wsEffects == action.getEffects();
}

bool UGOAPAction::operator!=(UGOAPAction& action)
{
	return !(*this == action);
}

FString UGOAPAction::getName()
{
	return this->name;
}

float UGOAPAction::getCost()
{
	return this->cost;
}

AActor* UGOAPAction::getTarget()
{
	return target;
}

GOAPWorldState UGOAPAction::getPreconditions()
{
	return wsPreconditions;
}

GOAPWorldState UGOAPAction::getEffects()
{
	return wsEffects;
}

void UGOAPAction::setName(FString n)
{
	this->name = n;
}

void UGOAPAction::setCost(float c)
{
	cost = c;
}

void UGOAPAction::setTarget(AActor* t)
{
	target = t;
}

void UGOAPAction::setPreconditions(GOAPWorldState preconditionStates)
{
	wsPreconditions = preconditionStates;
}

void UGOAPAction::setEffects(GOAPWorldState effectStates)
{
	wsEffects = effectStates;
}
