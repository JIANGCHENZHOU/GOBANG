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
	int gameStatus;//-1Ϊδ��ʼ 0Ϊ��ʼ;1Ϊʧ�� 2Ϊʤ�� 
	int player;//0Ϊ���壬1Ϊ����

	CRect rect;
	Chess chess;
public:
	CRect GetPos(double mouseX, double mouseY);//ȷ�����Ƿ�Χ
	int GetNum(double mouseNum, int condition);//condition  0Ϊ�� 1Ϊ��
	void SetRect(CRect rect);
	Chess GetChess();
	void ChangePlayer();
	int GetPlayer();
};

