#include "stdafx.h"
#include "Chess.h"

Chess::Chess()
{
}

Chess::Chess(CRect rect)
	: topStack(0)
{
	//初始化棋盘
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			map[i][j] = -1;
	for (int i = 0; i < 225; i++)
		chessStack[i] = -1;
	topStack = -1;
	this->rect = rect;

	SetParameter();
}


Chess::~Chess()
{
}


// 十位数为i，个位数为j
bool Chess::PushChess(CPoint xy ,int player)
{
	//map的行列号
	int i = xy.x - 1;
	int j = xy.y - 1;

	if (topStack>254 && map[i][j] != -1)
		return false;
	//压栈
	chessStack[++topStack] = xy;

	map[i][j] = player;
	return true;
}


bool Chess::PoPChess(CPoint& xy, int& player)
{
	if (topStack < 0)
		return false;
	xy = chessStack[topStack--];
	
	int i = xy.x - 1;
	int j = xy.y - 1;

	player = map[i][j];
	map[i][j] = -1;

	return true;
}


void Chess::SetParameter()
{
	int cbWeight;
	cbLeft = cbTop = 50;

	//棋盘线
	int wh = rect.right - cbLeft - 50;
	int hh = rect.bottom - cbTop - 50;

	if (wh < hh)
	{
		cbWeight = wh;
		cbTop = (rect.bottom - rect.top) / 2 - cbWeight / 2;
	}
	else
	{
		cbWeight = hh;
		cbLeft = (rect.right - rect.left) / 2 - cbWeight / 2;
	}

	cbPerWeight = cbWeight / 14;
	cbWeight = 14 * cbPerWeight;//整数化

	cbRight = cbLeft + cbWeight;
	cbBottom = cbTop + cbWeight;
}





int Chess::GetCbLeft()
{
	return cbLeft;
}


int Chess::GetCbRight()
{
	return cbRight;
}


int Chess::GetPerWeight()
{
	return cbPerWeight;
}


int Chess::GetCbTop()
{
	return cbTop;
}


int Chess::GetCbBottom()
{
	return cbBottom;
}


void Chess::ChangeMap(int x, int y, int player)
{
	map[x - 1][y - 1] = player;
}


int Chess::GetChessMapPlayer(int x, int y)
{
	return map[x][y];
}


void Chess::SetRect(CRect rect)
{
	this->rect = rect;
}


bool Chess::IsStackEmpty()
{
	if (topStack == -1)
		return true;
	else
	{
		return false;
	}
}


int Chess::GetTopStack()
{
	return topStack;
}

CPoint* Chess::GetChessStack()
{
	return chessStack;
}

CPoint Chess::GetStackOfTopElem()
{
	return chessStack[topStack];
}
