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
	int gameStatus;//-1为未开始 0为开始;1为失败 2为胜利 
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
};

