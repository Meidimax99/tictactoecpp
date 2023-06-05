#include "Board.h"

Board::Board()
{
	size_t size = 3;
	for (size_t x = 0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			state[x][y] = '-';
		}
	}
}

bool Board::isActionAllowed(Action *action) const
{
	auto position = action->getPosition();
	return state[position.first][position.second] == '-';
}

bool Board::applyAction(Action *action)
{
	if (!isActionAllowed(action)) {
		throw std::exception("Action is not allowed!");
	}
	auto position = action->getPosition();
	state[position.first][position.second] = action->getMarker();
	return false;
}

void Board::drawBoard()
{
	size_t size = 3;
	for (size_t x = 0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			std::cout << state[x][y];
			
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

char Board::winning()
{
	size_t size = 3;
	//Check linear wins
	for (size_t i = 0; i < size; i++) {
		if (state[i][0] != '-' && (state[i][0] == state[i][1] && state[i][0] == state[i][2])) {
			return state[i][0];
		}
		if (state[0][i] != '-' && (state[0][i] == state[1][i] && state[0][i] == state[2][i])) {
			return state[i][0];
		}
	}
	if (state[0][0] != '-' && (state[0][0] == state[1][1] && state[0][0] == state[2][2])) {
		return state[0][0];
	}
	if (state[0][2] != '-' && (state[0][2] == state[1][1] && state[0][2] == state[2][0])) {
		return state[0][2];
	}
	return '-';
}

bool Board::finished()
{
	if (!('-' == winning())) {
		return true;
	}

	size_t size = 3;
	for (size_t x = 0; x < size; x++) {
		for (size_t y = 0; y < size; y++) {
			if (state[x][y] == '-') {
				return false;
			}
		}
	}
	return true;
}
