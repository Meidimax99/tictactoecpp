#pragma once
#include <list>
#include <string>
#include "Action.h"
class GameResult
{
public:
	void print();
	void addAction(Action* action);
private:
	std::string player_id_won;
	std::string player_id_lost;
	std::list<Action*> history;
};

