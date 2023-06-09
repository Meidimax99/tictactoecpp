#pragma once
#include "Action.h"
#include <iostream>
class Board
{
public:
	Board(size_t height, size_t width);
	bool isActionAllowed(Action *action) const noexcept;
	bool applyAction(Action *action);
	void print() const noexcept;
private:
	char ** m_state;
	size_t m_width;
	size_t m_heigth;
};

