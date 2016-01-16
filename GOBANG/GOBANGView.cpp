
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
	ON_WM_CREATE()
	ON_COMMAND(ID_DOUBLE_GAME, &CGOBANGView::OnDoubleGame)
	ON_COMMAND(ID_REGRET_CHESS, &CGOBANGView::OnRegretChess)
END_MESSAGE_MAP()

// CGOBANGView 构造/析构

CGOBANGView::CGOBANGView()
	: drawStatus(-1)
	, ePoint(0)
	, eR(0)
{
	// TODO:  在此处添加构造代码;
	CRect rect = CRect(0, 0, 0, 0);
	manager = Manager(rect);
	m_menu.LoadMenuW(IDR_MAINFRAME);
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

	if (drawStatus == 0)//下棋绘制
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
		//font.CreatePointFont(500, _T("宋体"), pDC);//创建字体，1000为字体大小可改为其他数字
		//pDC->SelectObject(&font);
		CString str;
		AgainDlg dlg;
		if (gameStatus == 0)
			str = _T("黑棋胜");
		else
		{
			str = _T("白棋胜");
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

//显示棋盘
void CGOBANGView::ShowChessboard(CDC* pDC, CRect rect)
{
	int cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight;

	cbLeft = cbTop = cbRight = cbBottom = cbWeight = perWeight = 0;

	SetBackground(pDC,rect);//设置背景
	DrawChessLine(pDC, rect, cbLeft, cbTop, cbRight, cbBottom, cbWeight, perWeight);//画棋盘线
	DrawCBEllipse(pDC, cbLeft, cbTop, perWeight);
	DrawUserInfo(pDC, rect, cbLeft);
}


// 画棋盘实心黑圆
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
void CGOBANGView::SetBackground(CDC* pDC, CRect rect)
{
	//设置棋盘背景
	//	CDC ChessBoard;
	//	CBitmap m_chessBoard;
	//	HBITMAP hBitmap;
	//
	//	//hBmp = (HBITMAP)::LoadImage(NULL,"BG.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);//具体位置
	//	hBitmap = (HBITMAP)::LoadImage(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);//从资源文件中加载
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
		myBrush.CreateSolidBrush(RGB(0, 0, 0));//设置实心画刷
	else
		myBrush.CreateSolidBrush(RGB(255,255, 255));
	CBrush *oldBrush = pDC->SelectObject(&myBrush);

	pDC->Ellipse(posX - weight, posY - weight, posX + weight, posY + weight);
	pDC->SelectObject(oldBrush);
	myBrush.DeleteObject();
}


void CGOBANGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (manager.GetGameStatus() == 2)
	{
		CRect rect;
		CRect ellipse;
		int perWeight;

		GetClientRect(&rect);
		manager.SetRect(rect);
		perWeight = manager.GetChess().GetPerWeight();

		ellipse = manager.GetPos(point.x, point.y);

		if (ellipse.EqualRect(CRect(0, 0, 0, 0)))//无效操作
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

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


BOOL CGOBANGView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类
	//m_menu.LoadMenuW(IDR_MAINFRAME);
	//this->SetMenu(&m_menu);

	return CView::OnCommand(wParam, lParam);
}


void CGOBANGView::OnDoubleGame()
{
	// TODO:  在此添加命令处理程序代码
	manager.InitManager();//初始化
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
	// TODO:  在此添加命令处理程序代码
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

	font.CreatePointFont(cbLeft , L"宋体", NULL);
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
	str.Format(L"比分：%d : %d", score[0], score[1]);
	font.CreatePointFont(cbTop * 5, L"宋体", NULL);
	pDC->SelectObject(&font);
	pDC->DrawText(str, rect, DT_CENTER);//居中
}
