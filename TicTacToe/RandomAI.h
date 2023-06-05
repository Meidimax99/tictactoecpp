#pragma once
#include "Player.h"
#include <string>
class RandomAI : public Player
{
public:
	RandomAI(std::string id);
	virtual Action* getNextAction(Board * board);
	virtual void sendMessage();
};

