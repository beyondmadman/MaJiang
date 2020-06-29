#pragma once
#include "GameLogic.h"

// CDrawCardStatic

class CDrawCardStatic : public CStatic
{
	DECLARE_DYNAMIC(CDrawCardStatic)

public:
	CDrawCardStatic();
	virtual ~CDrawCardStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL Create(DWORD dwStyle, CRect &rect, CWnd *pParent, UINT id);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	//绘画扑克
    void DrawCard();
	//初始数据
	void InitData(BYTE Card[], BYTE Action[]);
	//初始化DC
	void InitUserDC(void);
	//重置界面
	void ResetView(void);
	//时间消息
	afx_msg void OnTimer(UINT nIDEvent);
public:
	BYTE m_bCard[14];
	BYTE m_bAction[14];
public:

	CDC                 m_BackDC;				
	CDC                 m_CardDC1;
	CDC                 m_CardDC2;
	CDC                 m_ComplexDC;			

	CBitmap             *m_pBackBmp;		
	CBitmap             *m_pCardBmp1;
	CBitmap             *m_pCardBmp2;
	CBitmap             m_ComplexBmp;		

	int                 m_BackWidth;			
	int                 m_BackHeight;			

	int                 m_CardWidth;		
	int                 m_CardHeight;
	int                 m_nTimer;
};


