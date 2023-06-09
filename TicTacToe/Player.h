#pragma once
#include "Action.h"
#include "Board.h"


class Player
{
public:
	Player(std::string id);
	virtual Action* getNextAction(Board *board) = 0;
	virtual void sendMessage(const std::string & message) = 0;
	void setMarker(char marker);
	char getMarker();
	std::string player_id;
	char marker;
};

