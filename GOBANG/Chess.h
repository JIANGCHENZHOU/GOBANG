#pragma once
class Chess
{
public:
	Chess();
	~Chess();
	int map[15][15];
	int chessStack[225];
	// 十位数为i，个位数为j
	bool PushChess(int xy, int player);
	bool PoPChess(int& xy, int& player);
private:
	int topStack;
};

