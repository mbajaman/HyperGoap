// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"

/**
 * 
 */
class HYPERGOAP_API GOAPNode
{
private:
	GOAPWorldState world;
	int h;
	float g;
	int parent;
	UGOAPAction* action;

public:
	GOAPNode();
	GOAPNode(UGOAPAction* a);

	bool operator==(GOAPNode n);

	/* GETS */
	int getH();
	float getG();
	float getF();
	int getParent();
	GOAPWorldState getWorld();
	UGOAPAction* getAction();

	/* SETS */
	void setH(int value);
	void setH(GOAPWorldState w);
	void setG(GOAPNode p);
	void setParent(int p);
	void setWorld(GOAPWorldState w);
	void SetAction(UGOAPAction* a);
};
