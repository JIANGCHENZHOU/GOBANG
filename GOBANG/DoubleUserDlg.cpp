// DoubleUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GOBANG.h"
#include "DoubleUserDlg.h"
#include "afxdialogex.h"

// DoubleUserDlg �Ի���

IMPLEMENT_DYNAMIC(DoubleUserDlg, CDialogEx)

DoubleUserDlg::DoubleUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DoubleUserDlg::IDD, pParent)
	, m_sPlayer1(_T("���1"))
	, m_sPlayer2(_T("���2"))
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


// DoubleUserDlg ��Ϣ�������


BOOL DoubleUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void DoubleUserDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	user.SetUserInfo(m_sPlayer1, m_sPlayer2);
	CDialogEx::OnOK();
}
