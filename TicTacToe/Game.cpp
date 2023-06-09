#include "Game.h"
#include "Board.h"

Game::Game(std::list<Player*> &&players, size_t height, size_t width, size_t streak_length): m_players(players), winning_streak_length(streak_length), m_board(height, width)
{
	if (m_players.empty()) 
	{
		throw std::exception("No players set!");
	}
	last = nullptr;
	size_t index = 0;
	for (auto& player : players) 
	{
		player->setMarker(markers[index]);
		index++;
	}
}

GameResult* Game::start()
{
	GameResult* result = new GameResult;
	auto it = std::begin(m_players);
	while (!this->finished()) 
	{
		auto player = *it;

		//Get and apply action
		auto next_action = player->getNextAction(&m_board);
		while (!m_board.isActionAllowed(next_action))
		{
			player->sendMessage("Illegal Move\n");
			next_action = player->getNextAction(&m_board);
		}
		m_board.applyAction(next_action);

		it++;

		//Reset Iterator
		if (std::end(m_players) == it)
		{
			it = m_players.begin();
		}
	}
	return result;
}

bool Game::finished()
{
	return false;
}

char Game::getWinningPlayer()
{
	return '-';
}


