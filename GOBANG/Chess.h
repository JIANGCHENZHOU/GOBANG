#pragma once
class Chess
{
public:
	Chess();
	~Chess();
	int map[15][15];
	int chessStack[225];
	// ʮλ��Ϊi����λ��Ϊj
	bool PushChess(int xy, int player);
	bool PoPChess(int& xy, int& player);
private:
	int topStack;
};

