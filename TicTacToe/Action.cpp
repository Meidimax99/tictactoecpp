#include "Action.h"

Action::Action(size_t x, size_t y, std::string id, char marker)
{
	player_id = id;
	position.first = x;
	position.second = y;
	this->marker = marker;
}

std::pair<size_t, size_t> Action::getPosition()
{
	return position;
}

char Action::getMarker()
{
	return marker;
}
