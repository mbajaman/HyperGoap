// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP/GOAPNode.h"

GOAPNode::GOAPNode()
{
	action = NULL;
	h = 0;
	g = 0;
}

GOAPNode::GOAPNode(UGOAPAction* a)
{
	action = a;
	if (a != NULL) g = a->getCost();
	else g = 0;
	h = 0;
}

bool GOAPNode::operator==(GOAPNode n)
{
	return action == n.getAction();
}

int GOAPNode::getH()
{
	return h;
}

float GOAPNode::getG()
{
	return g;
}

float GOAPNode::getF()
{
	return g + h;
}

int GOAPNode::getParent()
{
	return parent;
}

UGOAPAction* GOAPNode::getAction()
{
	return action;
}

GOAPWorldState GOAPNode::getWorld()
{
	return world;
}

void GOAPNode::setH(int value)
{
	h = value;
}

void GOAPNode::setH(GOAPWorldState w)
{
	for (auto itr : world.getStates())
	{
		auto aux = w.getStates().find(itr.first);
		if (aux != w.getStates().end())
		{
			if (itr.second != aux->second) h++;
		}
		else h++;
	}
}

void GOAPNode::setG(GOAPNode p)
{
	this->g += p.getG();
}

void GOAPNode::setParent(int p)
{
	this->parent = p;
}

void GOAPNode::setWorld(GOAPWorldState w)
{
	this->world = w;
}

void GOAPNode::SetAction(UGOAPAction* a)
{
	this->h = 0;
	this->g = a->getCost();
	this->action = a;
}