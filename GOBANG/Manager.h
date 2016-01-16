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

	CRect rect;//窗口大小
	Chess chess;//棋子类
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
	void SetGameStatus(int gameStatus);
	void EmptyChess();
	bool PopChess(CPoint& xy, int& player);
	bool PushChess(CPoint& xy, int& player);
private:
	CString sPlayer1;
	CString sPlayer2;
public:
	void SetPlayer1(CString sPlayer1);
	void SetPlayer2(CString sPlayer2);
	CString GetPlayer1Name();
	CString GetPlayer2Name();
private:
	int numOfWin1;//player1胜利次数
	int numOfWin2;//player2胜利次数
	bool isP1First;//player1是否执黑棋 
public:
	void InitManager();
	void SetNumOfWin(int player1, int player2);
	void GetNumOfWin(int& player1, int& player2);
	void ShowCurrentPlayer(int& player, int& color);
	void ChangeFirstPlayer();
};

