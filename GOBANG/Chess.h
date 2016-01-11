#pragma once
class Chess
{
public:
	Chess(CRect rect);
	~Chess();
	// 十位数为i，个位数为j
	bool PushChess(CPoint xy, int player);
	bool PoPChess(CPoint& xy, int& player);
private:
	int topStack;
	int map[15][15];
	CPoint chessStack[225];
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
	void ChangeMap(int x, int y, int player);
	int GetChessMapPlayer(int x, int y);
	void SetRect(CRect rect);
	bool IsStackEmpty();
	int GetTopStack();
	CPoint* GetChessStack();
	CPoint GetStackOfTopElem();
};

