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
	bool GetIsAgain();//�Ƿ�����һ��

private:
	CString sPlayer1;
	CString sPlayer2;
	bool isAgain;
	int colorOfPlayer1;//���1 ִ����ɫ 0Ϊ�� 1Ϊ��
public:
	void ChangeColorOfPlayer1();
	int GetColorOfPlayer1();
private:
	// score[0]Ϊ���1������score[1]λ���2����
	int score[2];
public:
	void PlusScore(int pos);
	int* GetScore();
	void InitUserInfo();
};

extern UserInfo user;