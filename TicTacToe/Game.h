#pragma once
#include "Player.h"
#include "Board.h"
#include "GameResult.h"
#include <memory>

class Game
{
public:
	Game(std::list<Player*> &&players, size_t height, size_t width, size_t streak_length);
	GameResult* start();
	bool finished();
	Player* getWinningPlayer();
private:
	std::list<Player*> m_players;
	size_t winning_streak_length;
	Board m_board;
	Action* last;
	const char* markers = "XOABCDEFGHIJKLMNPQRSTUVWYZabcdefghijklmnopqrstuvwxyz";
};

