#include "stdafx.h"
#include "Manager.h"

Manager::Manager()
{
}

Manager::Manager(CRect rect)
	: sPlayer1(_T(""))
	, sPlayer2(_T(""))
	, numOfWin1(0)
	, numOfWin2(0)
{
	this->rect = rect;
	gameStatus = -1;
	player = 0;
	chess = Chess(rect);
}


Manager::~Manager()
{
}


CRect Manager::GetPos(double mouseX, double mouseY)
{
	int numY = GetNum(mouseX,1);
	
	if (numY == -1)//边界外
		return CRect(0,0,0,0);
	
	int numX = GetNum(mouseY,0);

	if (numX == -1)
		return CRect(0, 0, 0, 0);

	if (chess.GetChessMapPlayer(numX - 1,numY - 1) != -1)//有棋子
		return CRect(0, 0, 0, 0);
	
	int x = chess.GetCbLeft() + (numY - 1)*chess.GetPerWeight();
	int y = chess.GetCbTop() + (numX - 1)*chess.GetPerWeight();

	//保存棋子，棋子压入栈
	CPoint xy = CPoint(numX, numY);
	chess.PushChess(xy, player);
	chess.ChangeMap(numX, numY, player);
	

	return CRect(x - chess.GetPerWeight() / 2, y - chess.GetPerWeight() / 2,
		x + chess.GetPerWeight() / 2, y + chess.GetPerWeight() / 2);
}


int Manager::GetNum(double mouseNum, int condition)
{

	int low, high, index;
	int perWeight = chess.GetPerWeight();
	if (condition == 0)
	{
		low = chess.GetCbTop();
		high = chess.GetCbBottom();
		index = chess.GetCbTop();
	}
	else if (condition == 1)
	{
		low = chess.GetCbLeft();
		high = chess.GetCbRight();
		index = chess.GetCbLeft();
	}

	if (mouseNum > high || mouseNum < low)//边界外
		return -1;


	while (low <mouseNum)
	{
			low += perWeight;
	}
	return (low - mouseNum) < (mouseNum - low + perWeight)
		? ((low - index) / perWeight) + 1
		: ((low - perWeight - index) / perWeight) + 1;
}


void Manager::SetRect(CRect rect)
{
	chess.SetRect(rect);
	chess.SetParameter();
	this->rect = rect;
}


Chess Manager::GetChess()
{
	return chess;
}


void Manager::ChangePlayer()
{
	if (player == 0)
	{
		player = 1;
	}
	else if (player == 1)
	{
		player = 0;
	}
}


int Manager::GetPlayer()
{
	return player;
}


// 获取已下过的棋子
bool Manager::GetChessman(CPoint cmAssemble[225], int& length, int& x, int& y, int& player)
{
	CPoint xy;
	if (length == 0)
		return false;
	else
	{
		xy = cmAssemble[length - 1];
		x = xy.x - 1;
		y = xy.y - 1;
		player = chess.GetChessMapPlayer(x, y);
		length--;
	}
	return true;
}


int Manager::CheckStatus(int k)
{
	if (k == 0)
		if (IsEnd())
		{
			gameStatus = player;
			return player;//决出胜负
		}

	return 2;
}

bool Manager::IsEnd()
{
	CPoint xy = chess.GetStackOfTopElem();
	int x = xy.x;
	int y = xy.y;
	int num = 0;
	bool b1 = true;
	bool b2 = true;
	for (int i = 1; i < 5; i++)//横线
	{
		if (chess.GetChessMapPlayer(x + i - 1, y - 1) == player && b1)
			num++;
		else
			b1 = false;
		if (chess.GetChessMapPlayer(x - i - 1, y - 1) == player&&b2&& x - i > 0)
			num++;
		else
			b2 = false;
		if (!b1&&!b2) break;
		if (num >= 4) return true;
	}
	
	for (int i = 1, num = 0, b1 = true, b2 = true; i < 5; i++)//竖线
	{
		if (chess.GetChessMapPlayer(x - 1, y + i - 1) == player&&b1)
			num++;
		else
			b1 = false;
		if (chess.GetChessMapPlayer(x - 1, y - i - 1) == player && b2 && y - i > 0)
			num++;
		else
			b2 = false;
		if (!b1&&!b2) break;
		if (num >= 4) return true;
	}

	for (int i = 1, num = 0, b1 = true, b2 = true; i < 5; i++)//主斜对角线
	{
		if (chess.GetChessMapPlayer(x + i - 1, y + i - 1) == player&&b1)
			num++;
		else
			b1 = false;
		if (chess.GetChessMapPlayer(x - i - 1, y - i - 1) == player && b2 && x-i>0 && y-i>0)
			num++;
		else
			b2 = false;
		if (!b1&&!b2) break;
		if (num >= 4) return true;
	}

	for (int i = 1, num = 0, b1 = true, b2 = true; i < 5; i++)//副斜对角线
	{
		if (chess.GetChessMapPlayer(x - i - 1, y + i - 1) == player&&b1 && x - i > 0)
			num++;
		else
			b1 = false;
		if (chess.GetChessMapPlayer(x + i - 1, y - i - 1) == player && b2 && y - i>0)
			num++;
		else
			b2 = false;
		if (!b1&&!b2) break;
		if (num >= 4) return true;
	}
	return false;
}


int Manager::GetGameStatus()
{
	return gameStatus;
}



void Manager::SetGameStatus(int gameStatus)
{
	this->gameStatus = gameStatus;
}


void Manager::EmptyChess()
{
	player = 0;
	chess.EmptyChess();
}


bool Manager::PopChess(CPoint& xy, int& player)
{
	return chess.PoPChess(xy, player);
}


bool Manager::PushChess(CPoint& xy, int& player)
{
	return chess.PushChess(xy, player);
}


void Manager::SetPlayer1(CString sPlayer1)
{
	this->sPlayer1 = sPlayer1;
}


void Manager::SetPlayer2(CString sPlayer2)
{
	this->sPlayer2 = sPlayer2;
}


CString Manager::GetPlayer1Name()
{
	return sPlayer1;
}


CString Manager::GetPlayer2Name()
{
	return sPlayer2;
}


void Manager::InitManager()
{
	EmptyChess();
	sPlayer1 = _T("");
	sPlayer2 = _T("");
	numOfWin1 = 0;
	numOfWin2 = 0;
	gameStatus = -1;
}


void Manager::SetNumOfWin(int player1, int player2)
{
	numOfWin1 = player1;
	numOfWin2 = player2;
}


void Manager::GetNumOfWin(int& player1, int& player2)
{
	player1 = numOfWin1;
	player2 = numOfWin2;
}
