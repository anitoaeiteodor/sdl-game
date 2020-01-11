#pragma once

#include "Animation.h"
#include <unordered_map>

enum class Command {
	IDLE, RUN, DEATH
};

class AnimationSystem {
	std::vector<Animation*> nodes;
	int nNodes;
	Uint16 currentNode;
	std::unordered_map<Uint32, Uint16> triggers;
public:
	AnimationSystem(int nodes);
	~AnimationSystem();
	void AddAnimation(Animation* a);
	void AddTrigger(Uint16 src, Uint16 dst, Command action);
	void ProcessInput(Command com);
	SDL_Texture* GetNextFrame();
	Uint16 GetCurrentNode();
};