#pragma once
#include "UserInfo.h"


// DoubleUserDlg �Ի���

class DoubleUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DoubleUserDlg)

public:
	DoubleUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DoubleUserDlg();

// �Ի�������
	enum { IDD = IDD_DOUBLEUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_sPlayer1;
	CString m_sPlayer2;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
