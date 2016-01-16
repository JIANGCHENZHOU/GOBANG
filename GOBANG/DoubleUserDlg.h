#pragma once
#include "UserInfo.h"


// DoubleUserDlg 对话框

class DoubleUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DoubleUserDlg)

public:
	DoubleUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DoubleUserDlg();

// 对话框数据
	enum { IDD = IDD_DOUBLEUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_sPlayer1;
	CString m_sPlayer2;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
