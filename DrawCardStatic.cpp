// DrawCardStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "MAJIANG.h"
#include "DrawCardStatic.h"
#include ".\drawcardstatic.h"


// CDrawCardStatic

IMPLEMENT_DYNAMIC(CDrawCardStatic, CStatic)
CDrawCardStatic::CDrawCardStatic()
{
    m_BackWidth = 360;			
	m_BackHeight = 90;

	for (BYTE i =0; i < 14; i++)
	{
		m_bCard[i] = 0;
		m_bAction[i] = 0;
	}
}

CDrawCardStatic::~CDrawCardStatic()
{
	if (m_pBackBmp != NULL)
	{
		delete m_pBackBmp;
		m_pBackBmp = NULL;
	}

	if (m_pCardBmp1 != NULL)
	{
		delete m_pCardBmp1;
		m_pCardBmp1 = NULL;
	}
	if (m_pCardBmp2 != NULL)
	{
		delete m_pCardBmp2;
		m_pCardBmp2 = NULL;
	}
}


BEGIN_MESSAGE_MAP(CDrawCardStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CDrawCardStatic 消息处理程序


void CDrawCardStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
    dc.BitBlt(0, 0, m_BackWidth, m_BackHeight, &m_ComplexDC, 0, 0, SRCCOPY);
	// 不为绘图消息调用CStatic::OnPaint()
}

BOOL CDrawCardStatic::Create(DWORD dwStyle, CRect &rect, CWnd *pParent, UINT id)
{
	// TODO: 在此添加专用代码和/或调用基类
	BOOL result ;
	result = CWnd::CreateEx(WS_EX_WINDOWEDGE , 
		NULL, NULL, dwStyle, 
		rect.left, rect.top, rect.Width(), rect.Height(),
		pParent->GetSafeHwnd(), (HMENU)id) ;

	InitUserDC();
	DrawCard();

	m_nTimer = SetTimer(1, 1, NULL);
	return result;
}

//初始数据
void CDrawCardStatic::InitData(BYTE Card[], BYTE Action[])
{
	for (BYTE i = 0; i < 14; i++)
	{
		m_bCard[i] = Card[i];
		m_bAction[i] = Action[i];
	}
}

//绘画扑克
void CDrawCardStatic::DrawCard()
{ 
	m_ComplexDC.BitBlt(0, 0, m_BackWidth, m_BackHeight, &m_BackDC, 0, 0, SRCCOPY);

	BYTE Count = 0;

	for (BYTE i = 0; i < 14; i++)
	{
		BYTE CardType = m_bAction[i];
        BYTE Index = m_bCard[i];

		if (Index == 0)
		{
			return;
		}

		switch (CardType)
		{
		//正常画牌
		case ACK_ZHENG:
			{
				m_ComplexDC.BitBlt(12 + Count * 24, 25, 24,35, &m_CardDC2,25 * (Index-1), 0, SRCCOPY);
				Count++;
				break;
			}
		//吃牌画牌
		case ACK_CHI:
			{
				m_ComplexDC.BitBlt(12 + Count * 24, 25, 24, 35, &m_CardDC1, 25 * (Index-1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 2) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index+1), 0, SRCCOPY);
				Count = Count + 3;
				break;
			}
	    //碰牌画牌
		case ACK_PENG:
			{
				m_ComplexDC.BitBlt(12 + Count * 24, 25, 24, 35, &m_CardDC1, 25 * (Index-1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index-1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 2) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index-1), 0, SRCCOPY);
				Count = Count + 3;
				break;
			}
		//明杠画牌
		case ACK_MGANG:
			{
				m_ComplexDC.BitBlt(12 + Count * 24, 25, 24, 35, &m_CardDC1, 25 * (Index-1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index - 1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 2) * 24, 25, 24, 35, &m_CardDC1, 25 * (Index - 1), 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 18, 24, 35, &m_CardDC1, 25 * (Index - 1), 0, SRCCOPY);
				Count = Count + 3;
				break;
			}
		//暗杠画牌
		case ACK_AGANG:
			{
				m_ComplexDC.BitBlt(12 + Count * 24, 25, 24, 35, &m_CardDC1, 25 * 34, 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 25, 24, 35, &m_CardDC1, 25 * 34, 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 2) * 24, 25, 24, 35, &m_CardDC1, 25 * 34, 0, SRCCOPY);
				m_ComplexDC.BitBlt(12 + (Count + 1) * 24, 18, 24, 35, &m_CardDC1, 25 * (Index - 1), 0, SRCCOPY);	
				Count = Count + 3;
				break;
			}
			
		}
	}
}

BOOL CDrawCardStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}

//初始化DC
void CDrawCardStatic::InitUserDC(void)
{
	
	CDC *pDC;
	pDC = GetDC();
	
	m_pBackBmp = new CBitmap;
	m_pBackBmp->LoadBitmap(IDB_BITMAP3);
	
	m_pCardBmp1 = new CBitmap;
	m_pCardBmp1->LoadBitmap(IDB_BITMAP1);
	
	m_pCardBmp2 = new CBitmap;
	m_pCardBmp2->LoadBitmap(IDB_BITMAP2);

	if (m_BackDC.GetSafeHdc() == NULL) 
	{
		m_BackDC.CreateCompatibleDC(pDC);
		m_BackDC.SelectObject(m_pBackBmp);
	}
	if (m_CardDC1.GetSafeHdc() == NULL) 
	{
		m_CardDC1.CreateCompatibleDC(pDC);
		m_CardDC1.SelectObject(m_pCardBmp1);
	}
	if (m_CardDC2.GetSafeHdc() == NULL)
	{
		m_CardDC2.CreateCompatibleDC(pDC);
		m_CardDC2.SelectObject(m_pCardBmp2);
	}
	if (m_ComplexDC.GetSafeHdc() == NULL) 
	{
		m_ComplexDC.CreateCompatibleDC(pDC);
		m_ComplexBmp.CreateCompatibleBitmap(pDC, m_BackWidth, m_BackHeight);
		m_ComplexDC.SelectObject(&m_ComplexBmp);
	}
}

//时间消息
void CDrawCardStatic::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    Invalidate(false);
	DrawCard();
	CStatic::OnTimer(nIDEvent);
}

//重置界面
void CDrawCardStatic::ResetView(void)
{
	for (BYTE i =0; i < 14; i++)
	{
		m_bCard[i] = 0;
		m_bAction[i] = 0;
	}
}
