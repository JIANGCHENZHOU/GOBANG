// DoubleUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GOBANG.h"
#include "DoubleUserDlg.h"
#include "afxdialogex.h"

// DoubleUserDlg 对话框

IMPLEMENT_DYNAMIC(DoubleUserDlg, CDialogEx)

DoubleUserDlg::DoubleUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DoubleUserDlg::IDD, pParent)
	, m_sPlayer1(_T("玩家1"))
	, m_sPlayer2(_T("玩家2"))
{

}

DoubleUserDlg::~DoubleUserDlg()
{
}

void DoubleUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STRPLAYER1, m_sPlayer1);
	DDX_Text(pDX, IDC_STRPLAYER2, m_sPlayer2);
}


BEGIN_MESSAGE_MAP(DoubleUserDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &DoubleUserDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// DoubleUserDlg 消息处理程序


BOOL DoubleUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void DoubleUserDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	user.SetUserInfo(m_sPlayer1, m_sPlayer2);
	CDialogEx::OnOK();
}
