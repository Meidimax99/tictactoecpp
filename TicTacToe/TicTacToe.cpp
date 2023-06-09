#include <iostream>
#include "ConsolePlayer.h"
#include "Game.h"
#include "GameResult.h"
int main()
{
	std::list<Player*> players;

	players.push_back(new ConsolePlayer("1"));
	//players.push_back(new ConsolePlayer("2"));
	//players.push_back(new ConsolePlayer("3"));
	//players.push_back(new ConsolePlayer("4"));

	Game game(std::move(players), 20, 20, 1);
	
	auto result = game.start();
	//result.print();
}

