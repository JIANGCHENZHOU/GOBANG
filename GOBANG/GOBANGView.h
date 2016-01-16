
// GOBANGView.h : CGOBANGView ��Ľӿ�
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
protected: // �������л�����
	CGOBANGView();
	DECLARE_DYNCREATE(CGOBANGView)

// ����
public:
	CGOBANGDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CGOBANGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	void ShowChessboard(CDC* pDC, CRect rect);
	// ������ʵ��Բ
	void DrawCBEllipse(CDC* pDC, int cbLeft, int cbTop, int perWeight);//�������ϵ�ʵ�ĺ�Բ
	// ���ñ���
	void SetBackground(CDC* pDC, CRect rect);
	void DrawChessLine(CDC* pDC, CRect rect, int& cbLeft, int& cbTop, int& cbRight, int& cbBottom, int& cbWeight, int& perWeight);//�������ߺ���
	void DrawChessman(CDC* pDC, int posX, int posY, int weight, int color);//���庯��
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	Manager manager;
	int drawStatus;
	// Բ����
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

#ifndef _DEBUG  // GOBANGView.cpp �еĵ��԰汾
inline CGOBANGDoc* CGOBANGView::GetDocument() const
   { return reinterpret_cast<CGOBANGDoc*>(m_pDocument); }
#endif

