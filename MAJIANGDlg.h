// MAJIANGDlg.h : ͷ�ļ�
//

#pragma once
//#include "afxwin.h"
//#include "afxcmn.h"
#include "BtnST.h"
#include "DrawCardStatic.h"
#include "GameLogic.h"
#include "CardFan.h"

// CMAJIANGDlg �Ի���
class CMAJIANGDlg : public CDialog
{
// ����
public:
	CMAJIANGDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAJIANG_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//���ð�ť
	afx_msg void OnBnClickedButReset();
	//���ͼ���
	afx_msg void OnBnClickedButCount();
    
	//�˿˰�ť
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
	//��ʼ����ť
	void InitialiseButtons();
    //��ʼ��DataCtrl
	void InitFanDataCtrl();
	//��ʼ���ؼ�
	void InitControl();
	//������ʾ
	void FanDataDisPlay();
    //������ť
	void CClickedButton();
	afx_msg void OnBnClickedChHdly();
	afx_msg void OnBnClickedChMshc();
	afx_msg void OnBnClickedChGskh();
	afx_msg void OnBnClickedChQgh();
	afx_msg void OnBnClickedChHjz();
	afx_msg void OnBnClickedRaDianpao();
	afx_msg void OnBnClickedRaZimo();

public:
	CButtonST                                   m_bt1;               //�˿˰�ť
	CButtonST                                   m_bt2;               //�˿˰�ť
	CButtonST                                   m_bt3;               //�˿˰�ť
	CButtonST                                   m_bt4;               //�˿˰�ť
    CButtonST                                   m_bt5;               //�˿˰�ť
	CButtonST                                   m_bt6;               //�˿˰�ť
	CButtonST                                   m_bt7;               //�˿˰�ť
	CButtonST                                   m_bt8;               //�˿˰�ť
	CButtonST                                   m_bt9;               //�˿˰�ť
	CButtonST                                   m_bt10;              //�˿˰�ť
	CButtonST                                   m_bt11;              //�˿˰�ť
	CButtonST                                   m_bt12;              //�˿˰�ť
	CButtonST                                   m_bt13;              //�˿˰�ť
	CButtonST                                   m_bt14;              //�˿˰�ť
	CButtonST                                   m_bt15;              //�˿˰�ť
	CButtonST                                   m_bt16;              //�˿˰�ť
	CButtonST                                   m_bt17;              //�˿˰�ť
	CButtonST                                   m_bt18;              //�˿˰�ť
	CButtonST                                   m_bt19;              //�˿˰�ť
	CButtonST                                   m_bt20;              //�˿˰�ť
	CButtonST                                   m_bt21;              //�˿˰�ť
	CButtonST                                   m_bt22;              //�˿˰�ť
	CButtonST                                   m_bt23;              //�˿˰�ť
	CButtonST                                   m_bt24;              //�˿˰�ť
	CButtonST                                   m_bt25;              //�˿˰�ť
	CButtonST                                   m_bt26;              //�˿˰�ť
	CButtonST                                   m_bt27;              //�˿˰�ť
	CButtonST                                   m_bt28;              //�˿˰�ť
	CButtonST                                   m_bt29;              //�˿˰�ť
	CButtonST                                   m_bt30;              //�˿˰�ť
	CButtonST                                   m_bt31;              //�˿˰�ť
	CButtonST                                   m_bt32;              //�˿˰�ť
	CButtonST                                   m_bt33;              //�˿˰�ť
	CButtonST                                   m_bt34;              //�˿˰�ť
	
public:
	CListCtrl                                    m_listFanData;                    //�����б�
	CDrawCardStatic                              m_DrawCardStatic;                 //�˿˴���
	CGameLogic                                   m_GameLogic;                      //��Ϸ�߼�
	CCardFan                                     m_CardFan;                        //��Ϸ����

public:
	BYTE                                         m_bCardIndex[34];                 //�˿�����
	BYTE                                         m_bIndex;                         //������ֵ
	BYTE                                         m_bCardMaxCount;                  //�����Ŀ
	BYTE                                         m_bCardData[14];                  //�˿�����                                         
	tagWeaveItem					             m_WeaveItemArray[4];			   //����˿�
	BYTE                                         m_WeaveCount;                     //�����Ŀ
	BYTE                                         m_bOperateAction[14];             //������Ӧ
	BYTE                                         m_nOperateCount;                  //������Ŀ
	BYTE                                         m_bHeCard;                        //�����˿�
public:
	CComboBox                                    m_comHua;
	
};
