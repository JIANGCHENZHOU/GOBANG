#pragma once
#include "Chess.h"
#include "atltypes.h"
class Manager
{
public:
	Manager(CRect rect);
	Manager();
	~Manager();
private:
	int gameStatus;//-1为未开始 2为开始;0为黑棋胜利 1为白棋胜利 
	int player;//0为黑棋，1为白棋

	CRect rect;
	Chess chess;
public:
	CRect GetPos(double mouseX, double mouseY);//确定覆盖范围
	int GetNum(double mouseNum, int condition);//condition  0为行 1为列
	void SetRect(CRect rect);
	Chess GetChess();
	void ChangePlayer();
	int GetPlayer();
	// 获取已下过的棋子
	bool GetChessman(CPoint cmAssemble[225], int& length, int& x, int& y, int& player);
	int CheckStatus(int k);//k=0 检查落子是否能判定输赢
	int GetStackOfTopElem();
	bool IsEnd();
	int GetGameStatus();
};

