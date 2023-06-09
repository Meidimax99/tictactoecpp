#pragma once
#include "Action.h"
#include <iostream>
class Board
{
public:
	Board(size_t height, size_t width);
	bool isActionAllowed(Action *action) const noexcept;
	void applyAction(Action *action);
	void print(std::ostream &stream) const noexcept;
	char ** m_state;
	size_t m_width;
	size_t m_height;
	size_t free;
};

