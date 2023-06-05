#include "Game.h"
#include "Board.h"

Game::Game(std::shared_ptr<Player> player_a, std::shared_ptr<Player> player_b): a(player_a), b(player_b)
{
	a->setMarker('X');
	b->setMarker('O');
}

GameResult* Game::start()
{
	GameResult* result = new GameResult;

	Board board;

	auto next = a;
	auto prev = b;
	while (!board.finished()) {
		board.drawBoard();
		auto action = next->getNextAction();

		while (!board.isActionAllowed(action)) {
			next->sendMessage("Action not allowed, try again");
			action = next->getNextAction(&board);
		}

		board.applyAction(action);

		result->addAction(action);
		auto temp = next;
		next = prev;
		prev = temp;
	}
	auto winner_marker = board.winning();
	if (winner_marker == a->getMarker()) {
		std::cout << "Player '" + a->player_id << "' won!" << std::endl;
	}
	else if (winner_marker == b->getMarker()) {
		std::cout << "Player '" + b->player_id << "' won!" << std::endl;
	}
	else {
		std::cout << "Its a draw!" << std::endl;
	}
	return result;
}
