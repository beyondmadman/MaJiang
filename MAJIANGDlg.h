// MAJIANGDlg.h : 头文件
//

#pragma once
//#include "afxwin.h"
//#include "afxcmn.h"
#include "BtnST.h"
#include "DrawCardStatic.h"
#include "GameLogic.h"
#include "CardFan.h"

// CMAJIANGDlg 对话框
class CMAJIANGDlg : public CDialog
{
// 构造
public:
	CMAJIANGDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAJIANG_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//重置按钮
	afx_msg void OnBnClickedButReset();
	//番型计算
	afx_msg void OnBnClickedButCount();
    
	//扑克按钮
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();

public:
	//初始化按钮
	void InitialiseButtons();
    //初始化DataCtrl
	void InitFanDataCtrl();
	//初始化控件
	void InitControl();
	//番型显示
	void FanDataDisPlay();
    //单击按钮
	void CClickedButton();
	afx_msg void OnBnClickedChHdly();
	afx_msg void OnBnClickedChMshc();
	afx_msg void OnBnClickedChGskh();
	afx_msg void OnBnClickedChQgh();
	afx_msg void OnBnClickedChHjz();
	afx_msg void OnBnClickedRaDianpao();
	afx_msg void OnBnClickedRaZimo();

public:
	CButtonST                                   m_bt1;               //扑克按钮
	CButtonST                                   m_bt2;               //扑克按钮
	CButtonST                                   m_bt3;               //扑克按钮
	CButtonST                                   m_bt4;               //扑克按钮
    CButtonST                                   m_bt5;               //扑克按钮
	CButtonST                                   m_bt6;               //扑克按钮
	CButtonST                                   m_bt7;               //扑克按钮
	CButtonST                                   m_bt8;               //扑克按钮
	CButtonST                                   m_bt9;               //扑克按钮
	CButtonST                                   m_bt10;              //扑克按钮
	CButtonST                                   m_bt11;              //扑克按钮
	CButtonST                                   m_bt12;              //扑克按钮
	CButtonST                                   m_bt13;              //扑克按钮
	CButtonST                                   m_bt14;              //扑克按钮
	CButtonST                                   m_bt15;              //扑克按钮
	CButtonST                                   m_bt16;              //扑克按钮
	CButtonST                                   m_bt17;              //扑克按钮
	CButtonST                                   m_bt18;              //扑克按钮
	CButtonST                                   m_bt19;              //扑克按钮
	CButtonST                                   m_bt20;              //扑克按钮
	CButtonST                                   m_bt21;              //扑克按钮
	CButtonST                                   m_bt22;              //扑克按钮
	CButtonST                                   m_bt23;              //扑克按钮
	CButtonST                                   m_bt24;              //扑克按钮
	CButtonST                                   m_bt25;              //扑克按钮
	CButtonST                                   m_bt26;              //扑克按钮
	CButtonST                                   m_bt27;              //扑克按钮
	CButtonST                                   m_bt28;              //扑克按钮
	CButtonST                                   m_bt29;              //扑克按钮
	CButtonST                                   m_bt30;              //扑克按钮
	CButtonST                                   m_bt31;              //扑克按钮
	CButtonST                                   m_bt32;              //扑克按钮
	CButtonST                                   m_bt33;              //扑克按钮
	CButtonST                                   m_bt34;              //扑克按钮
	
public:
	CListCtrl                                    m_listFanData;                    //番型列表
	CDrawCardStatic                              m_DrawCardStatic;                 //扑克窗口
	CGameLogic                                   m_GameLogic;                      //游戏逻辑
	CCardFan                                     m_CardFan;                        //游戏番型

public:
	BYTE                                         m_bCardIndex[34];                 //扑克索引
	BYTE                                         m_bIndex;                         //索引数值
	BYTE                                         m_bCardMaxCount;                  //最大数目
	BYTE                                         m_bCardData[14];                  //扑克数据                                         
	tagWeaveItem					             m_WeaveItemArray[4];			   //组合扑克
	BYTE                                         m_WeaveCount;                     //组合数目
	BYTE                                         m_bOperateAction[14];             //操作相应
	BYTE                                         m_nOperateCount;                  //操作数目
	BYTE                                         m_bHeCard;                        //和牌扑克
public:
	CComboBox                                    m_comHua;
	
};
