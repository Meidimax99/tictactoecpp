#include "Game.h"
#include "Board.h"
#include <algorithm> 
#include <sstream>

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

		last = next_action;

		it++;

		//Reset Iterator
		if (std::end(m_players) == it)
		{
			it = m_players.begin();
		}
		result->addAction(next_action);
	}
	std::stringstream sstream;
	m_board.print(sstream);
	auto str = sstream.str();

	auto winner = getWinningPlayer();
	for (auto& player : m_players)
	{
		player->sendMessage(str);
		player->sendMessage("Player " + winner->player_id + " won!");
	}
	return result;
}

bool Game::finished()
{
	if (m_board.free == 0)
	{
		return true;
	}
	if (nullptr == last)
	{
		return false;
	}
	auto last_position = last->getPosition();
	auto marker = last->getMarker();
	auto row = last_position.first;
	auto col = last_position.second;
	auto& board = m_board.m_state;
	//Horizontal Win
	//If board is not wide enough, this check is not necesarry
	if (m_board.m_width >= winning_streak_length)
	{
		auto first_check_col = std::max(0, (int)col - (int)winning_streak_length+1);
		auto last_check_col = std::min((int)m_board.m_width-1, (int)col + (int)winning_streak_length - 1);
		for (size_t start_check = first_check_col; start_check <= (last_check_col-(winning_streak_length-1)); start_check++)
		{
			for (size_t y = start_check; (y - start_check) < winning_streak_length; y++)
			{
				if(board[row][y] != marker)
				{ 
					start_check = y;
					break;
				}
				else if ((y - start_check) == winning_streak_length - 1)
				{
					return true;
				}
			}
		}
	}
	//Vertical check
	if (m_board.m_height >= winning_streak_length)
	{
		auto first_check_row = std::max(0, (int)row - (int)winning_streak_length + 1);
		auto last_check_row = std::min((int)m_board.m_height-1, (int)row + (int)winning_streak_length - 1);
		for (size_t start_check = first_check_row; start_check <= (last_check_row - (winning_streak_length - 1)); start_check++)
		{
			for (size_t x = start_check; (x - start_check) < winning_streak_length; x++)
			{
				if (board[x][col] != marker)
				{
					start_check = x;
					break;
				}
				else if ((x - start_check) == winning_streak_length - 1)
				{
					return true;
				}
			}
		}
	}
	//Diagonal check 
	if (m_board.m_height >= winning_streak_length && m_board.m_width >= winning_streak_length)
	{
		//Those parameters define a kind of a bounding box around the newly inserted marker
		auto first_check_col = std::max(0, (int)col - (int)winning_streak_length + 1);
		auto last_check_col = std::min((int)m_board.m_width-1, (int)col + (int)winning_streak_length - 1);
		auto first_check_row = std::max(0, (int)row - (int)winning_streak_length + 1);
		auto last_check_row = std::min((int)m_board.m_height-1, (int)row + (int)winning_streak_length - 1);

		{
			//Upper left corner of bounding box
			auto top_front_col_diff = col - first_check_col;
			auto top_front_row_diff = row - first_check_row;
			//This is the relative difference relative to the last inserted point to the top-left corner from which a check can be started
			auto max_diff_top_left = std::min(top_front_col_diff, top_front_row_diff);

			//lower right corner of bounding box
			auto bot_back_col_diff = last_check_col - col;
			auto bot_back_row_diff = last_check_row - row;
			auto max_diff_bot_right = std::min(bot_back_col_diff, bot_back_row_diff);

			int steps = std::max(((int)max_diff_top_left + (int)max_diff_bot_right + 1) - ((int)winning_streak_length - 1),0);

			for (size_t start_index = 0; start_index < steps; start_index++)
			{
				auto start_x = (row - max_diff_top_left) + start_index;
				auto start_y = (col - max_diff_top_left) + start_index;
				for (size_t check_index = 0; check_index < winning_streak_length; check_index++)
				{
					if (board[start_x + check_index][start_x + check_index] != marker)
					{
						start_index += check_index;
						break;
					}
					else if (check_index == winning_streak_length - 1)
					{
						return true;
					}
				}
			}
		}

		//Left bot to top right check
		
		{
			//lower left corner of bounding box
			auto top_front_col_diff = col - first_check_col;
			auto bot_front_row_diff = last_check_row - row;
			//This is the relative difference relative to the last inserted point to the top-left corner from which a check can be started
			auto max_diff_bot_left = std::min(top_front_col_diff, bot_front_row_diff);

			//lower right corner of bounding box
			auto top_right_col_diff = last_check_col - col;
			auto top_right_row_diff = row - first_check_row;
			auto max_diff_top_right = std::min(top_right_col_diff, top_right_row_diff);

			int steps = std::max(((int)max_diff_bot_left + (int)max_diff_top_right + 1) - ((int)winning_streak_length - 1), 0);

			for (size_t start_index = 0; start_index < steps; start_index++)
			{
				auto start_x = (row + max_diff_bot_left) + start_index;
				auto start_y = (col - max_diff_bot_left) + start_index;
				for (size_t check_index = 0; check_index < winning_streak_length; check_index++)
				{
					auto board_marker = m_board.m_state[start_x - check_index][start_y + check_index];
					if (board_marker != marker)
					{
						start_index += check_index;
						break;
					}
					else if (check_index == winning_streak_length - 1)
					{
						return true;
					}
				}
			}
		}
	}


	return false;
}

Player* Game::getWinningPlayer()
{
	if (m_board.free == 0)
	{
		return nullptr;
	}
	for (auto& player : m_players)
	{
		if (player->getMarker() == last->getMarker())
		{
			return player;
		}
	}
	return nullptr;
}


