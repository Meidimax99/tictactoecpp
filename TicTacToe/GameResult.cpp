#include "GameResult.h"

void GameResult::addAction(Action* action)
{
	history.push_back(action);
}
