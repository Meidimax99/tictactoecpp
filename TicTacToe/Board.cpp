#include "Board.h"

Board::Board(size_t height, size_t width): m_width(width), m_height(height)
{
	m_state = new char*[height];
	for (size_t index = 0; index < height; index++)
	{
		m_state[index] = new char[width];
	}
	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) {
			m_state[row][col] = '-';
		}
	}
	free = width * height;
}

bool Board::isActionAllowed(Action *action) const noexcept
{
	auto position = action->getPosition();
	if (position.first > m_height || position.second > m_width || free == 0) 
	{
		return false;
	}
	return m_state[position.first][position.second] == '-';
}

void Board::applyAction(Action *action)
{
	if (!isActionAllowed(action)) 
	{
		throw std::exception("Action is not allowed!");
	}
	auto position = action->getPosition();
	m_state[position.first][position.second] = action->getMarker();
	free--;
}

void Board::print(std::ostream &stream) const noexcept
{
	for (size_t x = 0; x < m_height; x++) {
		for (size_t y = 0; y < m_width; y++) {
			stream << m_state[x][y] << " ";
		}
		stream << std::endl;
	}
	stream << std::endl;
}

