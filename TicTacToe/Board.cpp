#include "Board.h"

Board::Board(size_t height, size_t width): m_width(width), m_heigth(height)
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
}

bool Board::isActionAllowed(Action *action) const noexcept
{
	auto position = action->getPosition();
	if (position.first > m_heigth || position.second > m_width) 
	{
		return false;
	}
	return m_state[position.first][position.second] == '-';
}

bool Board::applyAction(Action *action)
{
	if (!isActionAllowed(action)) 
	{
		throw std::exception("Action is not allowed!");
	}
	auto position = action->getPosition();
	m_state[position.first][position.second] = action->getMarker();
	return false;
}

void Board::print() const noexcept
{
	for (size_t x = 0; x < m_heigth; x++) {
		for (size_t y = 0; y < m_width; y++) {
			std::cout << m_state[x][y] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

