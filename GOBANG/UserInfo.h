#pragma once
class DoubleUserDlg;
class CGOBANGView;

class UserInfo
{
public:
	UserInfo();
	~UserInfo();
	void SetUserInfo(CString sPlayer1, CString sPlayer2);
	CString GetPlayer1();
	CString GetPlayer2();
	void SetIsAgain(bool b);
	bool GetIsAgain();//是否再来一局

private:
	CString sPlayer1;
	CString sPlayer2;
	bool isAgain;
	int colorOfPlayer1;//玩家1 执棋颜色 0为黑 1为白
public:
	void ChangeColorOfPlayer1();
	int GetColorOfPlayer1();
private:
	// score[0]为玩家1分数，score[1]位玩家2分数
	int score[2];
public:
	void PlusScore(int pos);
	int* GetScore();
	void InitUserInfo();
};

extern UserInfo user;