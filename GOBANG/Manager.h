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
	int gameStatus;//-1Ϊδ��ʼ 2Ϊ��ʼ;0Ϊ����ʤ�� 1Ϊ����ʤ�� 
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
	// ��ȡ���¹�������
	bool GetChessman(CPoint cmAssemble[225], int& length, int& x, int& y, int& player);
	int CheckStatus(int k);//k=0 ��������Ƿ����ж���Ӯ
	int GetStackOfTopElem();
	bool IsEnd();
	int GetGameStatus();
};

