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

	CRect rect;//���ڴ�С
	Chess chess;//������
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
	int numOfWin1;//player1ʤ������
	int numOfWin2;//player2ʤ������
	bool isP1First;//player1�Ƿ�ִ���� 
public:
	void InitManager();
	void SetNumOfWin(int player1, int player2);
	void GetNumOfWin(int& player1, int& player2);
	void ShowCurrentPlayer(int& player, int& color);
	void ChangeFirstPlayer();
};

