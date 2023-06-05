#pragma once
#include "Player.h"
#include <string>
#include <iostream>
class ConsolePlayer : public Player
{
public:
	ConsolePlayer(std::string id);
	virtual Action* getNextAction(Board* board);
	virtual void sendMessage(const std::string & message);

};

