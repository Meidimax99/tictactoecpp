#pragma once
#include <string>

class Action
{
public:

	Action(size_t x, size_t y, std::string id, char marker);
	std::pair<size_t, size_t> getPosition();
	char getMarker();


private:
	char marker;
	std::string player_id;
	std::pair<size_t, size_t> position;
};

