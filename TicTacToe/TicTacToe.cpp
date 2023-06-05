#include <iostream>
#include "ConsolePlayer.h"
#include "Game.h"
#include "GameResult.h"
int main()
{
	std::shared_ptr<Player> a(new ConsolePlayer("Human1"));
	std::shared_ptr<Player> b(new ConsolePlayer("Human2"));
	Game game(a, b);
	
	auto result = game.start();
	//result.print();
}

