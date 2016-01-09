
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
END_MESSAGE_MAP()

// CGOBANGView ����/����

CGOBANGView::CGOBANGView()
{
	// TODO:  �ڴ˴���ӹ������

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

	ShowChessboard(pDC);

	

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


void CGOBANGView::ShowChessboard(CDC* pDC)
{
	CRect rect;
	int cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight;
	GetClientRect(&rect);
	cbLeft = cbTop = cbRight = cbBottom = cbWeight = perWeight = 0;

	SetBackground(pDC,rect);//���ñ���
	DrawChessLine(pDC, rect, cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight);//��������
	DrawCBEllipse(pDC, cbLeft, cbTop, perWeight);//��ʵ��Բ

	DrawChessman(pDC, cbLeft, cbTop, perWeight/2,1);
	DrawChessman(pDC, cbLeft+perWeight, cbTop, perWeight / 2, 0);
}


// ������ʵ��Բ
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
void CGOBANGView::SetBackground(CDC* pDC ,CRect rect)
{
	//�������̱���
	CDC ChessBoard;
	CBitmap m_chessBoard;
	HBITMAP hBitmap;

	//hBmp = (HBITMAP)::LoadImage(NULL,"BG.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);//����λ��
	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);//����Դ�ļ��м���

	m_chessBoard.Attach(hBitmap);

	ChessBoard.CreateCompatibleDC(pDC);
	ChessBoard.SelectObject(m_chessBoard);

	pDC->BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &ChessBoard, 0, 0, SRCCOPY);
}


void CGOBANGView::DrawChessLine(CDC* pDC, CRect rect, int& cbLeft, int& cbTop, int& cbRight, int& cbBottom, int& cbWeight, int& perWeight)
{
	cbLeft = cbTop = 50;

	//������
	int wh = rect.right - cbLeft - 50;
	int hh = rect.bottom - cbTop - 50;

	if (wh < hh)
	{
		cbWeight = wh;
		cbTop = (rect.bottom - rect.top) / 2 - cbWeight / 2;
	}
	else
	{
		cbWeight = hh;
		cbLeft = (rect.right - rect.left) / 2 - cbWeight / 2;
	}

	perWeight = cbWeight / 14;
	cbWeight = 14 * perWeight;//������

	cbRight = cbLeft + cbWeight;
	cbBottom = cbTop + cbWeight;

	for (int i = 0; i < 15; i++)
	{
		pDC->MoveTo(cbLeft + perWeight*i, cbTop);
		pDC->LineTo(cbLeft + perWeight*i, cbBottom);
		pDC->MoveTo(cbLeft, cbTop + perWeight*i);
		pDC->LineTo(cbRight, cbTop + perWeight*i);
	}
}


bool CGOBANGView::DrawChessman(CDC* pDC, int posX, int posY, int weight, int color)
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
	return true;
}


void CGOBANGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CPoint point;
	CRect rect;
	int x, y;
	GetCursorPos(&point);
	GetClientRect(&rect);

	point.x
}
