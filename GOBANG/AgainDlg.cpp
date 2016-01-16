// AgainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GOBANG.h"
#include "AgainDlg.h"
#include "afxdialogex.h"


// AgainDlg 对话框

IMPLEMENT_DYNAMIC(AgainDlg, CDialogEx)

AgainDlg::AgainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AgainDlg::IDD, pParent)
{

}

AgainDlg::~AgainDlg()
{
}

void AgainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AgainDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AgainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AgainDlg 消息处理程序


void AgainDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	user.SetIsAgain(true);
	CDialogEx::OnOK();
}
