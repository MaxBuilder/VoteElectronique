#include "BulletinBoard.hpp"

std::vector<Bulletin *> &BulletinBoard::get_board() { return board; }

std::vector<Bulletin *> BulletinBoard::get_board_copy() { return board; }

std::vector<cpp_int> &BulletinBoard::get_sums() { return sums; }

bool BulletinBoard::verify()
{
	// verifier.verify();
	return false;
}

void BulletinBoard::cout_board()
{
	for (Bulletin *b : board)
	{
		b->cout_board();
	}
}