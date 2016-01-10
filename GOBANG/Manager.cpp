#include "stdafx.h"
#include "Manager.h"

Manager::Manager()
{
}

Manager::Manager(CRect rect)
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
	
	if (numY == -1)
		return CRect(0,0,0,0);
	
	int numX = GetNum(mouseY,0);

	if (numX == -1)
		return CRect(0, 0, 0, 0);

	if (chess.GetChessMap(numX,numY) != -1)//有棋子
		return CRect(0, 0, 0, 0);
	
	int x = chess.GetCbLeft() + (numY - 1)*chess.GetPerWeight();
	int y = chess.GetCbTop() + (numX - 1)*chess.GetPerWeight();

	//保存棋子，棋子压入栈
	chess.PushChess(numX * 10 + numY, player);
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
	rect = this->rect;
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
