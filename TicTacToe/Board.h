#pragma once
#include "Action.h"
#include "Game.h"
#include <iostream>
class Board
{
public:
	Board();
	bool isActionAllowed(Action *action) const;
	bool applyAction(Action *action);
	void drawBoard();
	char winning();
	bool finished();
private:
	char state[3][3];
};

