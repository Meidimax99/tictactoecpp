#include "Player.h"

Player::Player(std::string id): player_id(id)
{
	marker = '-';
}

void Player::setMarker(char marker)
{
	this->marker = marker;
}

char Player::getMarker()
{
	return marker;
}
