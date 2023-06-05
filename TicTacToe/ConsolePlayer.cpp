#include "ConsolePlayer.h"

ConsolePlayer::ConsolePlayer(std::string id) : Player(id)
{
}

//TODO validations
size_t getNumber() {
	std::string str;
	std::cin >> str;
	size_t num;
	try {
		num = std::stoi(str);
	}
	catch (std::invalid_argument& e) {
		//TODO dont do it
		std::cout << "Not a number, try again:" << std::endl;
		return getNumber();
	}
	return num;
}

Action* ConsolePlayer::getNextAction(Board* board) 
{
	board->drawBoard();
	std::cout << "Enter x position: ";
	size_t x = getNumber();
	std::cout << "Enter y position: ";
	size_t y = getNumber();
	std::cout << std::endl;

	return new Action(x, y, player_id, marker);
}

void ConsolePlayer::sendMessage(const std::string & message) {
	std::cout << message << std::endl;
}


