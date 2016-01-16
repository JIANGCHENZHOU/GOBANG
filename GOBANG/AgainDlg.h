#pragma once
#include "UserInfo.h"

// AgainDlg 对话框

class AgainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AgainDlg)

public:
	AgainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AgainDlg();

// 对话框数据
	enum { IDD = IDD_AGAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
