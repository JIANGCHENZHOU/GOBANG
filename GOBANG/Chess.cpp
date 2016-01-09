#include "stdafx.h"
#include "Chess.h"


Chess::Chess()
	: topStack(0)
{
	//��ʼ������
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			map[i][j] = -1;
	for (int i = 0; i < 225; i++)
		chessStack[i] = -1;
	topStack = -1;
}


Chess::~Chess()
{
}


// ʮλ��Ϊi����λ��Ϊj
bool Chess::PushChess(int xy ,int player)
{
	//map�����к�
	int i = xy / 10;
	int j = xy % 10;

	if (topStack>254 && map[i][j] != -1)
		return false;
	//ѹջ
	chessStack[topStack++] = xy;

	map[i][j] = player;
	return true;
}


bool Chess::PoPChess(int& xy, int& player)
{
	if (topStack < 0)
		return false;
	xy = chessStack[topStack--];
	
	int i = xy / 10;
	int j = xy % 10;

	player = map[i][j];
	map[i][j] = -1;

	return true;
}
