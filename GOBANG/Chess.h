#pragma once
class Chess
{
public:
	Chess(CRect rect);
	~Chess();
	// 十位数为i，个位数为j
	bool PushChess(int xy, int player);
	bool PoPChess(int& xy, int& player);
private:
	int topStack;
	int map[15][15];
	int chessStack[225];
	int cbLeft;
	int cbTop;
	int cbRight;
	int cbBottom;
	int cbPerWeight;
	CRect rect;
public:
	void SetParameter();
	Chess();
	int GetCbLeft();
	int GetCbRight();
	int GetPerWeight();
	int GetCbTop();
	int GetCbBottom();
};

