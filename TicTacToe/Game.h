#pragma once
class Player;
class GameResult;
#include "Player.h"
#include "GameResult.h"
#include <memory>

class Game
{
public:
	Game(std::shared_ptr<Player> player_a, std::shared_ptr<Player> player_b);

	GameResult* start();
private:
	std::shared_ptr<Player> a;
	std::shared_ptr<Player> b;
};

