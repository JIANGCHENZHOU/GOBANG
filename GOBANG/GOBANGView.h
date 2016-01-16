
// GOBANGView.h : CGOBANGView 类的接口
//

#pragma once
#include "Manager.h"
#include "atltypes.h"
#include "afxwin.h"
#include "DoubleUserDlg.h"
#include "AgainDlg.h"
#include "UserInfo.h"

class CGOBANGView : public CView
{
protected: // 仅从序列化创建
	CGOBANGView();
	DECLARE_DYNCREATE(CGOBANGView)

// 特性
public:
	CGOBANGDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CGOBANGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void ShowChessboard(CDC* pDC, CRect rect);
	// 画棋盘实心圆
	void DrawCBEllipse(CDC* pDC, int cbLeft, int cbTop, int perWeight);//画棋盘上的实心黑圆
	// 设置背景
	void SetBackground(CDC* pDC, CRect rect);
	void DrawChessLine(CDC* pDC, CRect rect, int& cbLeft, int& cbTop, int& cbRight, int& cbBottom, int& cbWeight, int& perWeight);//画棋盘线函数
	void DrawChessman(CDC* pDC, int posX, int posY, int weight, int color);//画棋函数
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	Manager manager;
	int drawStatus;
	// 圆参数
	CPoint ePoint;
	int eR;
	CMenu m_menu;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDoubleGame();
	afx_msg void OnRegretChess();
protected:
public:
	void DrawUserInfo(CDC* pDC, CRect rect, int cbLeft);
	void DrawScore(CDC* pDC, CRect rect, int cbTop);
};

#ifndef _DEBUG  // GOBANGView.cpp 中的调试版本
inline CGOBANGDoc* CGOBANGView::GetDocument() const
   { return reinterpret_cast<CGOBANGDoc*>(m_pDocument); }
#endif

