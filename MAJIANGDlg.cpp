// MAJIANGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MAJIANG.h"
#include "MAJIANGDlg.h"
#include ".\majiangdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMAJIANGDlg 对话框



CMAJIANGDlg::CMAJIANGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMAJIANGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIndex = 0;
    ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	m_bCardMaxCount = 0;
    ZeroMemory(m_bCardData,sizeof(m_bCardData));
	ZeroMemory(m_bCardData,sizeof(m_bCardData));
    m_nOperateCount = 0;
	ZeroMemory(m_bCardData,sizeof(m_bCardData));
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
    m_WeaveCount=0;
	m_bHeCard = -1;

}

void CMAJIANGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_bt1);
	DDX_Control(pDX, IDC_BUTTON2, m_bt2);
	DDX_Control(pDX, IDC_BUTTON3, m_bt3);
	DDX_Control(pDX, IDC_BUTTON4, m_bt4);
	DDX_Control(pDX, IDC_BUTTON5, m_bt5);
	DDX_Control(pDX, IDC_BUTTON6, m_bt6);
	DDX_Control(pDX, IDC_BUTTON7, m_bt7);
	DDX_Control(pDX, IDC_BUTTON8, m_bt8);
	DDX_Control(pDX, IDC_BUTTON9, m_bt9);
	DDX_Control(pDX, IDC_BUTTON10, m_bt10);
	DDX_Control(pDX, IDC_BUTTON11, m_bt11);
	DDX_Control(pDX, IDC_BUTTON12, m_bt12);
	DDX_Control(pDX, IDC_BUTTON13, m_bt13);
	DDX_Control(pDX, IDC_BUTTON14, m_bt14);
	DDX_Control(pDX, IDC_BUTTON15, m_bt15);
	DDX_Control(pDX, IDC_BUTTON16, m_bt16);
	DDX_Control(pDX, IDC_BUTTON17, m_bt17);
	DDX_Control(pDX, IDC_BUTTON18, m_bt18);
	DDX_Control(pDX, IDC_BUTTON19, m_bt19);
	DDX_Control(pDX, IDC_BUTTON20, m_bt20);
	DDX_Control(pDX, IDC_BUTTON21, m_bt21);
	DDX_Control(pDX, IDC_BUTTON22, m_bt22);
	DDX_Control(pDX, IDC_BUTTON23, m_bt23);
	DDX_Control(pDX, IDC_BUTTON24, m_bt24);
	DDX_Control(pDX, IDC_BUTTON25, m_bt25);
	DDX_Control(pDX, IDC_BUTTON26, m_bt26);
	DDX_Control(pDX, IDC_BUTTON27, m_bt27);
	DDX_Control(pDX, IDC_BUTTON28, m_bt28);
	DDX_Control(pDX, IDC_BUTTON29, m_bt29);
	DDX_Control(pDX, IDC_BUTTON30, m_bt30);
	DDX_Control(pDX, IDC_BUTTON31, m_bt31);
	DDX_Control(pDX, IDC_BUTTON32, m_bt32);
	DDX_Control(pDX, IDC_BUTTON33, m_bt33);
	DDX_Control(pDX, IDC_BUTTON34, m_bt34);
	DDX_Control(pDX, IDC_LIST, m_listFanData);
	DDX_Control(pDX, IDC_COM_HUA, m_comHua);
}

BEGIN_MESSAGE_MAP(CMAJIANGDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUT_RESET, OnBnClickedButReset)
	ON_BN_CLICKED(IDC_BUT_COUNT, OnBnClickedButCount)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, OnBnClickedButton34)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_CH_HDLY, OnBnClickedChHdly)
	ON_BN_CLICKED(IDC_CH_MSHC, OnBnClickedChMshc)
	ON_BN_CLICKED(IDC_CH_GSKH, OnBnClickedChGskh)
	ON_BN_CLICKED(IDC_CH_QGH, OnBnClickedChQgh)
	ON_BN_CLICKED(IDC_CH_HJZ, OnBnClickedChHjz)
	ON_BN_CLICKED(IDC_RA_DIANPAO, OnBnClickedRaDianpao)
	ON_BN_CLICKED(IDC_RA_ZIMO, OnBnClickedRaZimo)
END_MESSAGE_MAP()


// CMAJIANGDlg 消息处理程序

BOOL CMAJIANGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitialiseButtons();
	InitControl();
	InitFanDataCtrl();

	CRect rect, rc;	
	GetClientRect(rect);

	if(m_DrawCardStatic.GetSafeHwnd() != NULL)
		m_DrawCardStatic.DestroyWindow();

	rc.left = 10;
	rc.top = 210;
	rc.right =370;
	rc.bottom = 300;
	m_DrawCardStatic.Create(WS_CHILDWINDOW|WS_VISIBLE,rc,this,IDD_MAJIANG);

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CMAJIANGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMAJIANGDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();	
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMAJIANGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//重置界面
void CMAJIANGDlg::OnBnClickedButReset()
{
	m_bIndex = 0;
    ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	m_bCardMaxCount = 0;
    ZeroMemory(m_bCardData,sizeof(m_bCardData));
	ZeroMemory(m_bCardData,sizeof(m_bCardData));
    m_nOperateCount = 0;
	ZeroMemory(m_bCardData,sizeof(m_bCardData));
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
    m_WeaveCount = 0;  
	m_bHeCard = -1;
	m_DrawCardStatic.ResetView();
}

//番型计算
void CMAJIANGDlg::OnBnClickedButCount()
{
	//声明变量
	BYTE bHeType = m_GameLogic.IsHe(m_bCardIndex);
	
	if ((bHeType != HCT_NULL) && (m_bCardMaxCount == 14))
	{
		//声明变量
		tagHeItem HeItem;
		HeItem.cbMenFeng = 27;
		HeItem.cbQuanFeng = 27;
		HeItem.bZiMo = false;
		HeItem.bMiaoShouHuiChun = false;
		HeItem.bHaiDiLaoYue = false;
		HeItem.bGangShangKaiHua = false;
		HeItem.bQiangGangHe = false;
		HeItem.bHeJueZhang = false;

		//和牌类型
		HeItem.cbHeType = bHeType;
		
		//门风
		if (((CButton*)GetDlgItem(IDC_RA_ME_DONG))->GetCheck())
		{
			HeItem.cbMenFeng = 27;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_ME_NAN))->GetCheck())
		{
			HeItem.cbMenFeng = 28;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_ME_XI))->GetCheck())
		{
			HeItem.cbMenFeng = 29;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_ME_BEI))->GetCheck())
		{
			HeItem.cbMenFeng = 30;
		}

		//圈风
		if (((CButton*)GetDlgItem(IDC_RA_QU_DONG))->GetCheck())
		{
			HeItem.cbQuanFeng = 27;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_QU_NAN))->GetCheck())
		{
			HeItem.cbQuanFeng = 28;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_QU_XI))->GetCheck())
		{
			HeItem.cbQuanFeng = 29;
		}
		else if (((CButton*)GetDlgItem(IDC_RA_QU_BEI))->GetCheck())
		{
			HeItem.cbQuanFeng = 30;
		}
		
		//自摸
		if (((CButton*)GetDlgItem(IDC_RA_ZIMO))->GetCheck())
		{
			HeItem.bZiMo = true;
		}
		//妙手回春
		if (((CButton*)GetDlgItem(IDC_CH_MSHC))->GetCheck())
		{
			HeItem.bMiaoShouHuiChun = true;
		}
		//海底捞月
		if (((CButton*)GetDlgItem(IDC_CH_HDLY))->GetCheck())
		{
			HeItem.bHaiDiLaoYue = true;
		}
		//杠上开花
		if (((CButton*)GetDlgItem(IDC_CH_GSKH))->GetCheck())
		{
			HeItem.bGangShangKaiHua = true;
		}
		//抢杠和
		if (((CButton*)GetDlgItem(IDC_CH_QGH))->GetCheck())
		{
			HeItem.bQiangGangHe = true;
		}
		//和绝张
		if (((CButton*)GetDlgItem(IDC_CH_HJZ))->GetCheck())
		{
			HeItem.bHeJueZhang = true;
		}
        //花牌
		HeItem.bHua =m_comHua.GetCurSel();
		//和牌扑克
		HeItem.bHeCard = m_bHeCard;
	
		m_CardFan.StatisticsFan(m_bCardIndex,m_WeaveItemArray,m_WeaveCount,HeItem);
		FanDataDisPlay();
	}
	else 
	{
		::AfxMessageBox("诈和");
	}
}

//初始化安钮
void CMAJIANGDlg::InitialiseButtons(void)
{
	m_bt1.SetIcon(IDI_ICON1);
	m_bt2.SetIcon(IDI_ICON2);
	m_bt3.SetIcon(IDI_ICON3);
	m_bt4.SetIcon(IDI_ICON4);
	m_bt5.SetIcon(IDI_ICON5);
	m_bt6.SetIcon(IDI_ICON6);
	m_bt7.SetIcon(IDI_ICON7);
	m_bt8.SetIcon(IDI_ICON8);
	m_bt9.SetIcon(IDI_ICON9);
	m_bt10.SetIcon(IDI_ICON10);
	m_bt11.SetIcon(IDI_ICON11);
	m_bt12.SetIcon(IDI_ICON12);
	m_bt13.SetIcon(IDI_ICON13);
	m_bt14.SetIcon(IDI_ICON14);
	m_bt15.SetIcon(IDI_ICON15);
	m_bt16.SetIcon(IDI_ICON16);
	m_bt17.SetIcon(IDI_ICON17);
	m_bt18.SetIcon(IDI_ICON18);
	m_bt19.SetIcon(IDI_ICON19);
	m_bt20.SetIcon(IDI_ICON20);
	m_bt21.SetIcon(IDI_ICON21);
	m_bt22.SetIcon(IDI_ICON22);
	m_bt23.SetIcon(IDI_ICON23);
	m_bt24.SetIcon(IDI_ICON24);
	m_bt25.SetIcon(IDI_ICON25);
	m_bt26.SetIcon(IDI_ICON26);
	m_bt27.SetIcon(IDI_ICON27);
	m_bt28.SetIcon(IDI_ICON28);
	m_bt29.SetIcon(IDI_ICON29);
	m_bt30.SetIcon(IDI_ICON30);
	m_bt31.SetIcon(IDI_ICON31);
	m_bt32.SetIcon(IDI_ICON32);
	m_bt33.SetIcon(IDI_ICON33);
	m_bt34.SetIcon(IDI_ICON34);
}

//初始化控件
void CMAJIANGDlg::InitControl(void)
{
	m_comHua.SetCurSel(0);

	CButton* pBtn = NULL;
	pBtn = (CButton*)GetDlgItem(IDC_RA_ORDINARILY);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_RA_QU_DONG);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_RA_ME_DONG);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(IDC_RA_DIANPAO);
	pBtn->SetCheck(1);

	((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);

}

//初始化DataCtrl
void CMAJIANGDlg::InitFanDataCtrl(void)
{
	m_listFanData.InsertColumn(1, "序号", LVCFMT_CENTER, 50,-1);
	m_listFanData.InsertColumn(2, "番型", LVCFMT_CENTER, 100,-1);
	m_listFanData.InsertColumn(3, "番数", LVCFMT_CENTER, 65,-1);

}

//番型显示
void CMAJIANGDlg::FanDataDisPlay()
{
	m_listFanData.DeleteAllItems();
	m_CardFan.m_lFanList.sort();
	m_CardFan.m_lFanList.reverse();

	list<BYTE>::iterator i;
	BYTE bItem = 0;
	CString strFan, strFanShu, strItem;
    BYTE bFanShu = 0;
	for (i = m_CardFan.m_lFanList.begin(); i != m_CardFan.m_lFanList.end(); i++)
	{
		strItem.Format("%d",bItem + 1); 
		strFan = m_CardFan.FanTransform(*i);
		strFanShu = m_CardFan.FanShuTransform(*i);
		bFanShu += atoi(strFanShu);
		m_listFanData.InsertItem(bItem,strItem);
		m_listFanData.SetItemText(bItem, 1, strFan);
		m_listFanData.SetItemText(bItem, 2, strFanShu);
		bItem++;
	}
	m_listFanData.InsertItem(bItem," ");
	m_listFanData.SetItemText(bItem, 1, "-------------");
	m_listFanData.SetItemText(bItem, 2, "--------");
	bItem++;
	strFanShu.Format("%d",bFanShu); 
	m_listFanData.InsertItem(bItem," ");
	m_listFanData.SetItemText(bItem, 1, "合 计");
	m_listFanData.SetItemText(bItem, 2, strFanShu);
}

//一万
void CMAJIANGDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 1;
	CClickedButton();
}

//二万
void CMAJIANGDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 2;
	CClickedButton();
}

//三万
void CMAJIANGDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 3;
	CClickedButton();
}

//四万
void CMAJIANGDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 4;
	CClickedButton();
}

//五万
void CMAJIANGDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 5;
	CClickedButton();
}

//六万
void CMAJIANGDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 6;
	CClickedButton();
}

//七万
void CMAJIANGDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 7;
	CClickedButton();
}

//八万
void CMAJIANGDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 8;
	CClickedButton();
}

//九万
void CMAJIANGDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 9;
	CClickedButton();
}

//一筒
void CMAJIANGDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 10;
	CClickedButton();
}

//二筒
void CMAJIANGDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 11;
	CClickedButton();
}

//三筒
void CMAJIANGDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 12;
	CClickedButton();
}

//四筒
void CMAJIANGDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 13;
	CClickedButton();
}

//五筒
void CMAJIANGDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 14;
	CClickedButton();
}

//六筒
void CMAJIANGDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 15;
	CClickedButton();
}

//七筒
void CMAJIANGDlg::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 16;
	CClickedButton();
}

//八筒
void CMAJIANGDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 17;
	CClickedButton();
}

//九筒
void CMAJIANGDlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 18;
	CClickedButton();
}

//一索
void CMAJIANGDlg::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 19;
	CClickedButton();
}

//二索
void CMAJIANGDlg::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 20;
	CClickedButton();
}

//三索
void CMAJIANGDlg::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 21;
	CClickedButton();
}

//四索
void CMAJIANGDlg::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 22;
	CClickedButton();
}

//五索
void CMAJIANGDlg::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 23;
	CClickedButton();
}

//六索
void CMAJIANGDlg::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 24;
	CClickedButton();
}

//七索
void CMAJIANGDlg::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 25;
	CClickedButton();
}

//八索
void CMAJIANGDlg::OnBnClickedButton26()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 26;
	CClickedButton();
}

//九索
void CMAJIANGDlg::OnBnClickedButton27()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 27;
	CClickedButton();
}

//东风
void CMAJIANGDlg::OnBnClickedButton28()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 28;
	CClickedButton();
}

//南风
void CMAJIANGDlg::OnBnClickedButton29()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 29;
	CClickedButton();
}

//西风
void CMAJIANGDlg::OnBnClickedButton30()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 30;
	CClickedButton();
}

//北风
void CMAJIANGDlg::OnBnClickedButton31()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 31;
	CClickedButton();
}

//红中
void CMAJIANGDlg::OnBnClickedButton32()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 32;
	CClickedButton();
}

//白板
void CMAJIANGDlg::OnBnClickedButton33()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 33;
	CClickedButton();
}

//发财
void CMAJIANGDlg::OnBnClickedButton34()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIndex = 34;
	CClickedButton();
}

//单击处理
void CMAJIANGDlg::CClickedButton(void)
{
	if (m_bCardMaxCount == 14)
	{
		return;
	}

	//和牌
	if ((m_bCardMaxCount == 13)  && (m_bCardIndex[m_bIndex-1] < 4))
	{
		m_bHeCard = m_bIndex-1;
	}
    
	BYTE Type = ACK_NULL;

	// 正常操作
	if ((((CButton*)GetDlgItem(IDC_RA_ORDINARILY))->GetCheck()) && (m_bCardIndex[m_bIndex-1] < 4))
	{
		m_bCardIndex[m_bIndex-1]++;
		m_bCardMaxCount++;
        Type = ACK_ZHENG;
	}
	
    // 吃牌操作
	if ((((CButton*)GetDlgItem(IDC_RA_CHI))->GetCheck()) && (m_bCardIndex[m_bIndex-1] == 0) && (m_bCardMaxCount <= 9))
	{
		m_WeaveItemArray[m_WeaveCount].cbWeaveKind=ACK_CHI;
		m_WeaveItemArray[m_WeaveCount].cbCardIndex = m_bIndex-1;
        m_WeaveCount++;

		m_bCardMaxCount = m_bCardMaxCount + 3;
		Type = ACK_CHI;
	}

	// 碰牌操作
	if ((((CButton*)GetDlgItem(IDC_RA_PENG))->GetCheck()) && (m_bCardIndex[m_bIndex-1] <= 1) && (m_bCardMaxCount <= 9))
	{
		m_WeaveItemArray[m_WeaveCount].cbWeaveKind = ACK_PENG;
		m_WeaveItemArray[m_WeaveCount].cbCardIndex = m_bIndex-1;
        m_WeaveCount++;

		m_bCardMaxCount = m_bCardMaxCount + 3;
		Type = ACK_PENG;
	}

	// 明杠操作
	if ((((CButton*)GetDlgItem(IDC_RA_MI_GANG))->GetCheck()) && (m_bCardIndex[m_bIndex-1] == 0) && (m_bCardMaxCount <= 9))
	{
		m_WeaveItemArray[m_WeaveCount].cbWeaveKind = ACK_MGANG;
		m_WeaveItemArray[m_WeaveCount].cbCardIndex = m_bIndex-1;
        m_WeaveCount++;
		
		m_bCardMaxCount = m_bCardMaxCount + 3;
        Type = ACK_MGANG;
	}

	// 暗杠操作
	if ((((CButton*)GetDlgItem(IDC_RA_AN_GANG))->GetCheck()) && (m_bCardIndex[m_bIndex-1] == 0) && (m_bCardMaxCount <= 9))
	{
		m_WeaveItemArray[m_WeaveCount].cbWeaveKind = ACK_AGANG;
		m_WeaveItemArray[m_WeaveCount].cbCardIndex = m_bIndex-1;
        m_WeaveCount++;
		
		m_bCardMaxCount = m_bCardMaxCount + 3;
		Type = ACK_AGANG;
	}

	if (Type != ACK_NULL)
	{
		m_bCardData[m_nOperateCount] = m_bIndex;
		m_bOperateAction[m_nOperateCount] = Type;
		m_nOperateCount++;
		m_DrawCardStatic.InitData(m_bCardData,m_bOperateAction); 
	}
}

void CMAJIANGDlg::OnBnClickedChHdly()
{
	if (((CButton*)GetDlgItem(IDC_CH_HDLY))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
	    ((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
	}
}

void CMAJIANGDlg::OnBnClickedChMshc()
{
	if (((CButton*)GetDlgItem(IDC_CH_MSHC))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
	    ((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
	}
}

void CMAJIANGDlg::OnBnClickedChGskh()
{
	if (((CButton*)GetDlgItem(IDC_CH_GSKH))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
	    ((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
	}
}

void CMAJIANGDlg::OnBnClickedChQgh()
{
	if (((CButton*)GetDlgItem(IDC_CH_QGH))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_CH_HJZ))->EnableWindow(false);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_HJZ))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
	    ((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
	}
}

void CMAJIANGDlg::OnBnClickedChHjz()
{
	if (((CButton*)GetDlgItem(IDC_CH_HJZ))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(true);
        
		if (((CButton*)GetDlgItem(IDC_RA_DIANPAO))->GetCheck())
		{
			((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
			((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
		}
		else
		{
			((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
			((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
		}
	}
}

void CMAJIANGDlg::OnBnClickedRaDianpao()
{
	((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_CH_GSKH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_CH_MSHC))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CH_HJZ))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(true);
}

void CMAJIANGDlg::OnBnClickedRaZimo()
{
    ((CButton*)GetDlgItem(IDC_CH_GSKH))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_CH_MSHC))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_CH_HJZ))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_CH_QGH))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_CH_HDLY))->EnableWindow(false);
	((CButton*)GetDlgItem(IDC_CH_QGH))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_CH_HDLY))->SetCheck(0);
}
