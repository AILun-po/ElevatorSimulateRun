// ElevatorGifView.h : interface of the CElevatorGifView class
//
/////////////////////////////////////////////////////////////////////////////

#include "Elevator.h"

#if !defined(AFX_ELEVATORGIFVIEW_H__6DCDC7E7_6B6A_4C40_9107_88D39A3B615F__INCLUDED_)
#define AFX_ELEVATORGIFVIEW_H__6DCDC7E7_6B6A_4C40_9107_88D39A3B615F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CElevatorGifView : public CView
{
protected: // create from serialization only
	CElevatorGifView();
	DECLARE_DYNCREATE(CElevatorGifView)

// Attributes
public:
	CElevatorGifDoc* GetDocument();
public:
	void init(CDC*);
	//将第n个电梯按dir方式移动
	void MoveEle_n(CDC *, int n,int dir);
	void Ele_Up(CDC *,int n);
	void Ele_Down(CDC *, int n);
	void Ele_Open(CDC *, int n);
	void Ele_Close(CDC *, int n);
	void PassengerDiv();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElevatorGifView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CElevatorGifView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CElevatorGifView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CRect mrect;
	CRect mainRect;
	//6个电梯
	Elevator elevator[6];
	//电梯的位置
	int eleLocation[6];
	//电梯的宽和高
	int ewidth, eheight;
	//框的宽和高
	int width,height;
	//楼层 和 电梯数
	int floor, elenum;
	//楼的起点 终点
	int ex0, ey0, ex1, ey1;
};

#ifndef _DEBUG  // debug version in ElevatorGifView.cpp
inline CElevatorGifDoc* CElevatorGifView::GetDocument()
   { return (CElevatorGifDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEVATORGIFVIEW_H__6DCDC7E7_6B6A_4C40_9107_88D39A3B615F__INCLUDED_)
