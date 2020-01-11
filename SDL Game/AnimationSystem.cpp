#include "AnimationSystem.h"
#include "Game.h"
#include <iostream>

AnimationSystem::AnimationSystem(int nodes)
{
	nNodes = nodes;
	triggers.clear();
	this->nodes.clear();
	currentNode = 0;
}

AnimationSystem::~AnimationSystem()
{
	for (auto& anim : nodes)
	{
		if(anim)
			delete anim;
		anim = nullptr;
	}
	triggers.clear();
	nodes.clear();
}

void AnimationSystem::AddAnimation(Animation* a)
{
	nodes.push_back(a);
}

void AnimationSystem::AddTrigger(Uint16 src, Uint16 dst, Command action)
{
	Uint32 hash = (src << 16) | (Uint16)action;
	triggers[hash] = dst;
	//std::cout << hash << ' ' << dst << '\n';
}

void AnimationSystem::ProcessInput(Command com)
{
	Uint32 hash = (currentNode << 16) | (Uint16)com;
	if (triggers[hash])
	{
		//std::cout << hash << '\n';
		currentNode = triggers[hash];
		std::cout << "Changed animation to " << currentNode << " node\n";
	}
	else
	{
		//std::cout << hash << '\n';
		currentNode = 0;
		//std::cout << "Changed animation to " << currentNode << " node\n";
	}
}

SDL_Texture* AnimationSystem::GetNextFrame()
{
	return nodes[currentNode]->GetNextFrame();
}

Uint16 AnimationSystem::GetCurrentNode()
{
	return nodes[currentNode]->GetCurrentFrame();
}
