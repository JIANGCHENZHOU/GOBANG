
// GOBANGView.cpp : CGOBANGView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CGOBANGView 构造/析构

CGOBANGView::CGOBANGView()
{
	// TODO:  在此处添加构造代码

}

CGOBANGView::~CGOBANGView()
{
}

BOOL CGOBANGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGOBANGView 绘制

void CGOBANGView::OnDraw(CDC* pDC)
{
	CGOBANGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	ShowChessboard(pDC);

	

	// TODO:  在此处为本机数据添加绘制代码
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


// CGOBANGView 诊断

#ifdef _DEBUG
void CGOBANGView::AssertValid() const
{
	CView::AssertValid();
}

void CGOBANGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGOBANGDoc* CGOBANGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGOBANGDoc)));
	return (CGOBANGDoc*)m_pDocument;
}
#endif //_DEBUG


// CGOBANGView 消息处理程序


void CGOBANGView::ShowChessboard(CDC* pDC)
{
	CRect rect;
	int cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight;
	GetClientRect(&rect);
	cbLeft = cbTop = cbRight = cbBottom = cbWeight = perWeight = 0;

	SetBackground(pDC,rect);//设置背景
	DrawChessLine(pDC, rect, cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight);//画棋盘线
	DrawCBEllipse(pDC, cbLeft, cbTop, perWeight);//画实心圆

	DrawChessman(pDC, cbLeft, cbTop, perWeight/2,1);
	DrawChessman(pDC, cbLeft+perWeight, cbTop, perWeight / 2, 0);
}


// 画棋盘实心圆
void CGOBANGView::DrawCBEllipse(CDC* pDC ,int cbLeft, int cbTop ,int perWeight)
{
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(0, 0, 0));//设置实心画刷
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

	pDC->SelectObject(oldBrush);//用回旧刷
	myBrush.DeleteObject();

}

// 设置背景
void CGOBANGView::SetBackground(CDC* pDC ,CRect rect)
{
	//设置棋盘背景
	CDC ChessBoard;
	CBitmap m_chessBoard;
	HBITMAP hBitmap;

	//hBmp = (HBITMAP)::LoadImage(NULL,"BG.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);//具体位置
	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);//从资源文件中加载

	m_chessBoard.Attach(hBitmap);

	ChessBoard.CreateCompatibleDC(pDC);
	ChessBoard.SelectObject(m_chessBoard);

	pDC->BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top, &ChessBoard, 0, 0, SRCCOPY);
}


void CGOBANGView::DrawChessLine(CDC* pDC, CRect rect, int& cbLeft, int& cbTop, int& cbRight, int& cbBottom, int& cbWeight, int& perWeight)
{
	cbLeft = cbTop = 50;

	//棋盘线
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
	cbWeight = 14 * perWeight;//整数化

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
		myBrush.CreateSolidBrush(RGB(0, 0, 0));//设置实心画刷
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CPoint point;
	CRect rect;
	int x, y;
	GetCursorPos(&point);
	GetClientRect(&rect);

	point.x
}
