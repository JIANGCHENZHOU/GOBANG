#pragma once
#include "UserInfo.h"

// AgainDlg �Ի���

class AgainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AgainDlg)

public:
	AgainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AgainDlg();

// �Ի�������
	enum { IDD = IDD_AGAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
