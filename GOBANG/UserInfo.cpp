#include "stdafx.h"
#include "UserInfo.h"

UserInfo user;

UserInfo::UserInfo()
{
	InitUserInfo();
}


UserInfo::~UserInfo()
{
}


void UserInfo::SetUserInfo(CString sPlayer1, CString sPlayer2)
{
	this->sPlayer1 = sPlayer1;
	this->sPlayer2 = sPlayer2;
}


CString UserInfo::GetPlayer1()
{
	return sPlayer1;
}


CString UserInfo::GetPlayer2()
{
	return sPlayer2;
}

void UserInfo::SetIsAgain(bool b)
{
	isAgain = b;
}

bool UserInfo::GetIsAgain()
{
	return isAgain;
}

void UserInfo::ChangeColorOfPlayer1()
{
	colorOfPlayer1 == 1 ? colorOfPlayer1 = 0 : colorOfPlayer1 = 1;
}


int UserInfo::GetColorOfPlayer1()
{
	return colorOfPlayer1;
}


void UserInfo::PlusScore(int pos)
{
	if (pos > 2 || pos < 0)
		MessageBox(AfxGetMainWnd()->m_hWnd, L"¼Ó·Ö³ö´í", NULL, NULL);
	else
		score[pos]++;
}

int* UserInfo::GetScore()
{
	return score;
}


void UserInfo::InitUserInfo()
{
	score[0] = score[1] = 0;
	colorOfPlayer1 = 0;
	sPlayer1 = _T("");
	sPlayer2 = _T("");
	isAgain = false;
}
