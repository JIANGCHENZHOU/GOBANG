// AgainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GOBANG.h"
#include "AgainDlg.h"
#include "afxdialogex.h"


// AgainDlg �Ի���

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


// AgainDlg ��Ϣ�������


void AgainDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	user.SetIsAgain(true);
	CDialogEx::OnOK();
}
