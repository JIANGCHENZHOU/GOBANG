
// GOBANGView.cpp : CGOBANGView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "GOBANG.h"
#endif

#include "GOBANGDoc.h"
#include "GOBANGView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGOBANGView

IMPLEMENT_DYNCREATE(CGOBANGView, CView)

BEGIN_MESSAGE_MAP(CGOBANGView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_DOUBLE_GAME, &CGOBANGView::OnDoubleGame)
	ON_COMMAND(ID_REGRET_CHESS, &CGOBANGView::OnRegretChess)
END_MESSAGE_MAP()

// CGOBANGView ����/����

CGOBANGView::CGOBANGView()
	: drawStatus(-1)
	, ePoint(0)
	, eR(0)
{
	// TODO:  �ڴ˴���ӹ������;
	CRect rect = CRect(0, 0, 0, 0);
	manager = Manager(rect);
	m_menu.LoadMenuW(IDR_MAINFRAME);
}

CGOBANGView::~CGOBANGView()
{
}

BOOL CGOBANGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGOBANGView ����

void CGOBANGView::OnDraw(CDC* pDC)
{
	CGOBANGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	int gameStatus = manager.GetGameStatus();

	GetClientRect(&rect);
	manager.SetRect(rect);

	ShowChessboard(pDC, rect);
	
	int w = manager.GetChess().GetPerWeight();
	int l = manager.GetChess().GetCbLeft();
	int t = manager.GetChess().GetCbTop();
	if (!manager.GetChess().IsStackEmpty())
	{
		int length = manager.GetChess().GetTopStack() + 1;
		int x, y, player;
			while (manager.GetChessman(manager.GetChess().GetChessStack(), length, x, y, player))
			DrawChessman(pDC, y*w + l, x*w + t, w/2, player);
	}

	if (drawStatus == 0)//�������
	{
		DrawChessman(pDC, ePoint.x, ePoint.y, eR,manager.GetPlayer());
		drawStatus = 2;
		if (manager.CheckStatus(0) == 0 || manager.CheckStatus(0) == 1)
			Invalidate();
		manager.ChangePlayer();
	}
	
	if (gameStatus == 2)
		DrawScore(pDC, rect, t);

	if (gameStatus == 0 || gameStatus== 1)
	{
		//CFont font;
		//font.CreatePointFont(500, _T("����"), pDC);//�������壬1000Ϊ�����С�ɸ�Ϊ��������
		//pDC->SelectObject(&font);
		CString str;
		AgainDlg dlg;
		if (gameStatus == 0)
			str = _T("����ʤ");
		else
		{
			str = _T("����ʤ");
		}
		DrawScore(pDC, rect, t);
		MessageBox(str);
		dlg.DoModal();
		if (user.GetIsAgain())
		{
			user.SetIsAgain(false);
			int pos;
			user.GetColorOfPlayer1() == gameStatus ? pos = 0 : pos = 1;
			user.PlusScore(pos);
			int* score = user.GetScore();
			manager.SetNumOfWin(score[0], score[1]);
			user.ChangeColorOfPlayer1();
			manager.EmptyChess();
			manager.SetGameStatus(2);
			DrawScore(pDC, rect, t);
			Invalidate();
		}
		else
		{
			user.InitUserInfo();
			manager.InitManager();
			Invalidate();
		}
	}
	
	
		
	
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CGOBANGView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGOBANGView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGOBANGView ���

#ifdef _DEBUG
void CGOBANGView::AssertValid() const
{
	CView::AssertValid();
}

void CGOBANGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGOBANGDoc* CGOBANGView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGOBANGDoc)));
	return (CGOBANGDoc*)m_pDocument;
}
#endif //_DEBUG


// CGOBANGView ��Ϣ�������

//��ʾ����
void CGOBANGView::ShowChessboard(CDC* pDC, CRect rect)
{
	int cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight;

	cbLeft = cbTop = cbRight = cbBottom = cbWeight = perWeight = 0;

	SetBackground(pDC,rect);//���ñ���
	DrawChessLine(pDC, rect, cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight);//��������
	DrawCBEllipse(pDC, cbLeft, cbTop, perWeight);
	DrawUserInfo(pDC, rect, cbLeft);
}


// ������ʵ�ĺ�Բ
void CGOBANGView::DrawCBEllipse(CDC* pDC ,int cbLeft, int cbTop ,int perWeight)
{
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(0, 0, 0));//����ʵ�Ļ�ˢ
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	int x = cbLeft + perWeight * 3;
	int y = cbTop + perWeight * 3;
	int w = perWeight/5;
	pDC->Ellipse(x - w, y - w, x + w, y + w);

	x = cbLeft + perWeight * 11;
	y = cbTop + perWeight * 11;
	pDC->Ellipse(x - w, y - w, x + w, y + w);

	x = cbLeft + perWeight * 11;
	y = cbTop + perWeight * 3;
	pDC->Ellipse(x - w, y - w, x + w, y + w);

	x = cbLeft + perWeight * 3;
	y = cbTop + perWeight * 11;
	pDC->Ellipse(x - w, y - w, x + w, y + w);

	x = cbLeft + perWeight * 7;
	y = cbTop + perWeight * 7;
	pDC->Ellipse(x - w, y - w, x + w, y + w);

	pDC->SelectObject(oldBrush);//�ûؾ�ˢ
	myBrush.DeleteObject();

}

// ���ñ���
void CGOBANGView::SetBackground(CDC* pDC, CRect rect)
{
	//�������̱���
	//	CDC ChessBoard;
	//	CBitmap m_chessBoard;
	//	HBITMAP hBitmap;
	//
	//	//hBmp = (HBITMAP)::LoadImage(NULL,"BG.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);//����λ��
	//	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);//����Դ�ļ��м���
	//
	//	m_chessBoard.Attach(hBitmap);
	//
	//	ChessBoard.CreateCompatibleDC(pDC);
	//	ChessBoard.SelectObject(m_chessBoard);
	//
	//	pDC->BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &ChessBoard, 0, 0, SRCCOPY);
	//
	
	pDC->FillSolidRect(rect, RGB(192, 192, 192));
}


void CGOBANGView::DrawChessLine(CDC* pDC, CRect rect, int& cbLeft, int& cbTop, int& cbRight, int& cbBottom, int& cbWeight, int& perWeight)
{
	Chess chess;
	//GetParameter(rect, cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight);
	//manager.SetRect(rect);
	chess = manager.GetChess();
	cbLeft = chess.GetCbLeft();
	cbRight = chess.GetCbRight();
	cbTop = chess.GetCbTop();
	cbBottom = chess.GetCbBottom();
	perWeight = chess.GetPerWeight();

	for (int i = 0; i < 15; i++)
	{
		pDC->MoveTo(cbLeft + perWeight*i, cbTop);
		pDC->LineTo(cbLeft + perWeight*i, cbBottom);
		pDC->MoveTo(cbLeft, cbTop + perWeight*i);
		pDC->LineTo(cbRight, cbTop + perWeight*i);
	}
}


void CGOBANGView::DrawChessman(CDC* pDC, int posX, int posY, int weight, int color)
{
	CBrush myBrush;
	if (color == 0)
		myBrush.CreateSolidBrush(RGB(0, 0, 0));//����ʵ�Ļ�ˢ
	else
		myBrush.CreateSolidBrush(RGB(255,255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->Ellipse(posX - weight, posY - weight, posX + weight, posY + weight);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}


void CGOBANGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (manager.GetGameStatus() == 2)
	{
		CRect rect;
		CRect ellipse;
		int perWeight;

		GetClientRect(&rect);
		manager.SetRect(rect);
		perWeight = manager.GetChess().GetPerWeight();

		ellipse = manager.GetPos(point.x, point.y);

		if (ellipse.EqualRect(CRect(0, 0, 0, 0)))//��Ч����
			return;
		ePoint.y = ellipse.top + perWeight / 2;
		ePoint.x = ellipse.left + perWeight / 2;
		eR = perWeight / 2;
		drawStatus = 0;



		InvalidateRect(ellipse, FALSE);
	}
}

int CGOBANGView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	this->SetMenu(&m_menu);
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	return 0;
}


BOOL CGOBANGView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//m_menu.LoadMenuW(IDR_MAINFRAME);
	//this->SetMenu(&m_menu);

	return CView::OnCommand(wParam, lParam);
}


void CGOBANGView::OnDoubleGame()
{
	// TODO:  �ڴ���������������
	manager.InitManager();//��ʼ��
	user.InitUserInfo();
	
	DoubleUserDlg dlg;
	dlg.DoModal();
	manager.SetPlayer1(user.GetPlayer1());
	manager.SetPlayer2(user.GetPlayer2());

	manager.SetGameStatus(2);
	Invalidate();
}

void CGOBANGView::OnRegretChess()
{
	// TODO:  �ڴ���������������
	CPoint xy;
	int player;
	if (manager.PopChess(xy, player) && manager.GetGameStatus() == 2)
	{
		manager.ChangePlayer();
		Invalidate();
	}
}

void CGOBANGView::DrawUserInfo(CDC* pDC, CRect rect, int cbLeft)
{
	int heigth = rect.bottom - rect.top;
	CFont font;
	heigth /= 4;

	font.CreatePointFont(cbLeft , L"����", NULL);
	pDC->SelectObject(&font);

	pDC->TextOutW(rect.left, heigth, manager.GetPlayer1Name());
	pDC->TextOutW(rect.left, heigth*3, manager.GetPlayer2Name());
}


void CGOBANGView::DrawScore(CDC* pDC,CRect rect,int cbTop)
{
	CString str;
	CFont font;
	int score[2];
	manager.GetNumOfWin(score[0], score[1]);
	str.Format(L"�ȷ֣�%d : %d", score[0], score[1]);
	font.CreatePointFont(cbTop * 5, L"����", NULL);
	pDC->SelectObject(&font);
	pDC->DrawText(str, rect, DT_CENTER);//����
}
