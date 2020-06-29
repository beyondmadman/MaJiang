#include "StdAfx.h"
#include ".\cardfan.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CCardFan::CCardFan(void)
{
	//扑克变量
	ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	ZeroMemory(m_bHandCardIndex,sizeof(m_bHandCardIndex));
	ZeroMemory(m_bAllCard,sizeof(m_bAllCard));
	m_bAllCardNum = 0;

	//顺子变量
	ZeroMemory(m_bShunZi,sizeof(m_bShunZi));            
	m_bShunZiNum = 0;            
	m_bChiNum = 0;               

	//刻子变量
	ZeroMemory(m_bKeZi,sizeof(m_bKeZi));             
	m_bKeZiNum = 0;              
	m_bMingKeNum = 0;            
	m_bAnKeNum = 0;              

	//杠牌变量
	ZeroMemory(m_bGang,sizeof(m_bGang));              
	m_bGangNum = 0;              
	m_bMingGangNum = 0;          
	m_bAnGangNum = 0;            

	//将牌变量
	m_bJiang = 0;              
}

//析构函数
CCardFan::~CCardFan(void)
{
}

//拆分扑克
void CCardFan::SplitCard(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//重置变量
	ResetGameVariable();

	//拆分扑克
	SplitCardShunKe(cbCardIndex,WeaveItem,bItemCount);

	//条件判断
	if (!((IsYiSeSiTongShun(m_bShunZi,m_bShunZiNum)) || (IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))))
	{
		SplitCardKeShun(cbCardIndex,WeaveItem,bItemCount);
	}
}

//拆分扑克
void CCardFan::SplitCardShunKe(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//重置变量
	ResetGameVariable();

	//扑克变量
	BYTE cbTempCardIndex[MAX_INDEX];
	CopyMemory(cbTempCardIndex,cbCardIndex,sizeof(cbTempCardIndex));
	CopyMemory(m_bCardIndex,cbCardIndex,sizeof(m_bCardIndex));
	CopyMemory(m_bHandCardIndex,cbCardIndex,sizeof(m_bHandCardIndex));

	for (BYTE i = 0; i < bItemCount; i++)
	{
		switch (WeaveItem[i].cbWeaveKind)
		{
		case ACK_CHI:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex]++;
				m_bCardIndex[WeaveItem[i].cbCardIndex + 1]++;
				m_bCardIndex[WeaveItem[i].cbCardIndex + 2]++;
				break;
			}
		case ACK_PENG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		case ACK_MGANG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		case ACK_AGANG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		}
	}

	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		for (BYTE j = 0; j < m_bCardIndex[i]; j++)
		{
			m_bAllCard[m_bAllCardNum++] = i;
		}

		if (m_bAllCardNum == MAX_COUNT)
		{
			break;
		}
	}

	//拆分组合扑克
	for (BYTE i = 0; i < bItemCount; i++)
	{
		switch (WeaveItem[i].cbWeaveKind)
		{
		case ACK_CHI:
			{
				m_bShunZi[m_bShunZiNum] = WeaveItem[i].cbCardIndex;
				m_bShunZiNum++;
				m_bChiNum++;
				break;
			}
		case ACK_PENG:
			{
				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bMingKeNum++;
				break;
			}
		case ACK_MGANG:
			{
				m_bGang[m_bGangNum] = WeaveItem[i].cbCardIndex;
				m_bGangNum++;
				m_bMingGangNum++;

				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bMingKeNum++;
				break;
			}
		case ACK_AGANG:
			{
				m_bGang[m_bGangNum] = WeaveItem[i].cbCardIndex;
				m_bGangNum++;
				m_bAnGangNum++;
				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bAnKeNum++;
				break;
			}
		}
	}

	//拆分手中扑克

	//顺子
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] != 0)
		{
			BYTE bCardNum = cbTempCardIndex[i];
			for (BYTE j = 0; j < bCardNum; j++)
			{
				if ((cbTempCardIndex[i + 1] != 0) && (cbTempCardIndex[i + 2] != 0))
				{
					cbTempCardIndex[i]--;
					cbTempCardIndex[i + 1]--;
					cbTempCardIndex[i + 2]--;

					if (m_GameLogic.IsHe(cbTempCardIndex) != HCT_NULL)
					{
						m_bShunZi[m_bShunZiNum] = i;
						m_bShunZiNum++;
					}
					else
					{
						cbTempCardIndex[i]++;
						cbTempCardIndex[i + 1]++;
						cbTempCardIndex[i + 2]++;
					}
				}
			}
		}
	}

	//刻子
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] > 2)
		{
			cbTempCardIndex[i] -= 3;

			if (m_GameLogic.IsHe(cbTempCardIndex) != HCT_NULL)
			{
				m_bKeZi[m_bKeZiNum] = i;
				m_bKeZiNum++;
				m_bAnKeNum++;
			}
			else
			{
				cbTempCardIndex[i] += 3;
			}
		}
	}

	//将牌
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] > 1)
		{
			cbTempCardIndex[i] -= 2;

			if (m_GameLogic.IsHe(cbTempCardIndex) != HCT_NULL)
			{
				m_bJiang = i;
			}
			else
			{
				cbTempCardIndex[i] += 2;
			}
		}
	}
}

//拆分扑克
void CCardFan::SplitCardKeShun(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//重置变量
	ResetGameVariable();

	//扑克变量
	BYTE cbTempCardIndex[MAX_INDEX];
	CopyMemory(cbTempCardIndex,cbCardIndex,sizeof(cbTempCardIndex));
	CopyMemory(m_bCardIndex,cbCardIndex,sizeof(m_bCardIndex));
	CopyMemory(m_bHandCardIndex,cbCardIndex,sizeof(m_bHandCardIndex));


	for (BYTE i = 0; i < bItemCount; i++)
	{
		switch (WeaveItem[i].cbWeaveKind)
		{
		case ACK_CHI:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex]++;
				m_bCardIndex[WeaveItem[i].cbCardIndex + 1]++;
				m_bCardIndex[WeaveItem[i].cbCardIndex + 2]++;
				break;
			}
		case ACK_PENG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		case ACK_MGANG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		case ACK_AGANG:
			{
				m_bCardIndex[WeaveItem[i].cbCardIndex] += 3;
				break;
			}
		}
	}

	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		for (BYTE j = 0; j < m_bCardIndex[i]; j++)
		{
			m_bAllCard[m_bAllCardNum++] = i;
		}

		if (m_bAllCardNum == MAX_COUNT)
		{
			break;
		}
	}

	//拆分组合扑克
	for (BYTE i = 0; i < bItemCount; i++)
	{
		switch (WeaveItem[i].cbWeaveKind)
		{
		case ACK_CHI:
			{
				m_bShunZi[m_bShunZiNum] = WeaveItem[i].cbCardIndex;
				m_bShunZiNum++;
				m_bChiNum++;
				break;
			}
		case ACK_PENG:
			{
				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bMingKeNum++;
				break;
			}
		case ACK_MGANG:
			{
				m_bGang[m_bGangNum] = WeaveItem[i].cbCardIndex;
				m_bGangNum++;
				m_bMingGangNum++;

				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bMingKeNum++;
				break;
			}
		case ACK_AGANG:
			{
				m_bGang[m_bGangNum] = WeaveItem[i].cbCardIndex;
				m_bGangNum++;
				m_bAnGangNum++;
				m_bKeZi[m_bKeZiNum] = WeaveItem[i].cbCardIndex;
				m_bKeZiNum++;
				m_bAnKeNum++;
				break;
			}
		}
	}

	//拆分手中扑克

	//刻子
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] > 2)
		{
			cbTempCardIndex[i] -= 3;

			if (m_GameLogic.IsHe(cbTempCardIndex) != HCT_NULL)
			{
				m_bKeZi[m_bKeZiNum] = i;
				m_bKeZiNum++;
				m_bAnKeNum++;
			}
			else
			{
				cbTempCardIndex[i] += 3;
			}
		}
	}

	//顺子
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] != 0)
		{
			BYTE bCardNum = cbTempCardIndex[i];
			for (BYTE j = 0; j < bCardNum; j++)
			{
				if ((cbTempCardIndex[i + 1] != 0) && (cbTempCardIndex[i + 2] != 0))
				{
					cbTempCardIndex[i]--;
					cbTempCardIndex[i + 1]--;
					cbTempCardIndex[i + 2]--;

					if (m_GameLogic.IsHe(cbTempCardIndex))
					{
						m_bShunZi[m_bShunZiNum] = i;
						m_bShunZiNum++;
					}
					else
					{
						cbTempCardIndex[i]++;
						cbTempCardIndex[i + 1]++;
						cbTempCardIndex[i + 2]++;
					}
				}
			}
		}
	}

	//将牌
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (cbTempCardIndex[i] > 1)
		{
			cbTempCardIndex[i] -= 2;

			if (m_GameLogic.IsHe(cbTempCardIndex) != HCT_NULL)
			{
				m_bJiang = i;
			}
			else
			{
				cbTempCardIndex[i] += 2;
			}
		}
	}
}

//重置变量
void CCardFan::ResetGameVariable()
{
	//扑克变量
	ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	ZeroMemory(m_bHandCardIndex,sizeof(m_bHandCardIndex));
	ZeroMemory(m_bAllCard,sizeof(m_bAllCard));
	m_bAllCardNum = 0;

	//顺子变量
	ZeroMemory(m_bShunZi,sizeof(m_bShunZi));            
	m_bShunZiNum = 0;            
	m_bChiNum = 0;               

	//刻子变量
	ZeroMemory(m_bKeZi,sizeof(m_bKeZi));             
	m_bKeZiNum = 0;              
	m_bMingKeNum = 0;            
	m_bAnKeNum = 0;              

	//杠牌变量
	ZeroMemory(m_bGang,sizeof(m_bGang));              
	m_bGangNum = 0;              
	m_bMingGangNum = 0;          
	m_bAnGangNum = 0;            

	//将牌变量
	m_bJiang = 0;       
}

//统计番型
void CCardFan::StatisticsFan(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount, tagHeItem HeItem)
{
	//拆分扑克
	SplitCard(cbCardIndex,WeaveItem,bItemCount);

	m_HeItem.cbMenFeng = HeItem.cbMenFeng;
	m_HeItem.cbQuanFeng = HeItem.cbQuanFeng;
	m_HeItem.bZiMo = HeItem.bZiMo;
	m_HeItem.bMiaoShouHuiChun = HeItem.bMiaoShouHuiChun;
	m_HeItem.bHaiDiLaoYue = HeItem.bHaiDiLaoYue;
	m_HeItem.bGangShangKaiHua = HeItem.bGangShangKaiHua;
	m_HeItem.bQiangGangHe = HeItem.bQiangGangHe;
	m_HeItem.bHeJueZhang = HeItem.bHeJueZhang;
	m_HeItem.bHeCard = HeItem.bHeCard;
	
	m_bYaoJiuKe = true;
	m_bMenQuanFeng = true;
	m_bBuMen = true; 
	m_bDuanYao = true;
	m_bSiGuiYi = true;
	m_bQuanDaiYao = true;
	m_bPengPengHe = true;
	m_bQingYiSe = true;
	m_bPingHe = true;
	m_bWuZi = true;
	m_bDanDiaoJiang = true;
	m_bQueYiMen = true;
	m_bShuangAnKe = true;
	m_bJianKe = true;
	m_bShuangTongKe = true;
	m_bZiMo = true;
	m_bHeJueZhang = true;

	m_lFanList.clear();

	//和牌类型
	switch (HeItem.cbHeType)
	{
	case HCT_QDHU:
		{  
			if (IsYiSeShuangLongHui(m_bShunZi,m_bShunZiNum,m_bJiang) || IsYiSeSiTongShun(m_bShunZi,m_bShunZiNum))
			{
				PuTongFan();
			}
			else 
			{
				QiDuiFan();
			}
			break;
		}
	case HCT_PTHU:
		{
			PuTongFan();
			break;
		}
	case HCT_SSYHU:
		{
			ShiSanYaoFan();            
			break;
		}
	case HCT_QXBKHU:
		{
			QiXingBuKaoFan();
			break;
		}
	case HCT_ZHLHU:
		{
			ZuHeLongFan();
			break;
		}
	case HCT_QBKHU:
		{
			QuanBuKaoFan();
			break;
		}
	}

	//花牌
	for (BYTE i = 0; i < HeItem.bHua; i++)
	{
		m_lFanList.push_back(13);
	}

	//无番和
	BOOL bWuFanHe = true;
	list<BYTE>::iterator iterFan;
	for (iterFan = m_lFanList.begin(); iterFan != m_lFanList.end(); iterFan++)	
	{
		if (*iterFan != 13)
		{
			bWuFanHe = false;
		}
	}
	if (bWuFanHe)
	{
		m_lFanList.push_back(43);
	}
}


//普通番型
void CCardFan::PuTongFan()
{
	//杠牌番型
	GangFan();
	//刻子番型
	KeZiFan();
	//顺子番型
	ShunZiFan();
	//其他番型
	QiTaFan();
}

//刻子番型
void CCardFan::KeZiFan()
{
	if (m_bKeZiNum == 4)      //四刻子
	{
		KeZiFan_1Part();
	}
	else if (m_bKeZiNum == 3) //三刻子
	{
		KeZiFan_2Part();
	}
	else if (m_bKeZiNum == 2) //双刻子
	{
		KeZiFan_3Part();
	}

	if (IsJiuBaoLianDeng(m_bAllCard,m_bChiNum,m_bMingKeNum,m_bGangNum))
	{
		m_bYaoJiuKe = false;
	}

	KeZiFan_4Part();
}

//刻子番型
void CCardFan::KeZiFan_1Part()
{
	//大四喜
	if (IsDaSiXi(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(76);
		m_bMenQuanFeng = false;
		m_bYaoJiuKe = false;
		m_bPengPengHe = false;

		//四暗刻
		if (IsSiAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(73);
			m_bBuMen = false;
			m_bDanDiaoJiang = false;

			//字一色
			if (IsZiYiSe(m_bAllCard))
			{
				m_lFanList.push_back(71);
				m_bQingYiSe = false;
			}
			//混幺九
			else if (IsHunYaoJiu(m_bAllCard))
			{
				m_lFanList.push_back(64);
				m_bQuanDaiYao = false;
			}
		}
		//字一色
		else if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bQingYiSe = false;
		}
		//混幺九
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bQuanDaiYao = false;
		}
	}
	//清幺九
	else if (IsQingYaoJiu(m_bAllCard))
	{
		m_lFanList.push_back(74);
		m_bYaoJiuKe = false;
		m_bQuanDaiYao = false;
		m_bPengPengHe = false;

		//四暗刻
		if (IsSiAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(73);
			m_bBuMen = false;
			m_bDanDiaoJiang = false;
		}
	}
	//四暗刻
	else if (IsSiAnKe(m_bAnKeNum))
	{
		m_lFanList.push_back(73);
		m_bBuMen = false;
		m_bPengPengHe = false;
		m_bDanDiaoJiang = false;

		//字一色
		if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bYaoJiuKe = false;
			m_bQingYiSe = false;
		}
		//一色四节高
		else if (IsYiSeSiJieGao(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(67);
			m_bPengPengHe = false;
		}
		//混幺九
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bYaoJiuKe = false;
			m_bQuanDaiYao = false;
		}
		//全双刻
		else if (IsQuanShuangKe(m_bKeZi,m_bKeZiNum,m_bJiang))
		{
			m_lFanList.push_back(58);
			m_bDuanYao = false;
			m_bWuZi = false;
			
		}
	}
	//字一色
	else if (IsZiYiSe(m_bAllCard))
	{
		m_lFanList.push_back(71);
		m_bYaoJiuKe = false;
		m_bQingYiSe = false;
		m_bPengPengHe = false;
	}
	//一色四节高
	else if (IsYiSeSiJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(67);
		m_bPengPengHe = false;
	}
	//混幺九
	else if (IsHunYaoJiu(m_bAllCard))
	{
		m_lFanList.push_back(64);
		m_bYaoJiuKe = false;
		m_bQuanDaiYao = false;
	}
	//全双刻
	else if (IsQuanShuangKe(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(58);
		m_bPengPengHe = false;
		m_bDuanYao = false;
		m_bWuZi = false;
		
	}

	KeZiFan_2Part();
}

//刻子番型
void CCardFan::KeZiFan_2Part()
{
	//大三元
	if (IsDaSanYuan(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(75);
		m_bJianKe = false;
		m_bYaoJiuKe = false;
		
		//三暗刻
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//小四喜
	else if (IsXiaoSiXi(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(70);

		//三暗刻
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//一色三节高
	else if (IsYiSeSanJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(59);

		//三暗刻
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//三同刻
	else if (IsSanTongKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(54);
		m_bShuangTongKe = false;

		//三暗刻
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//三暗刻
	else if (IsSanAnKe(m_bAnKeNum))
	{
		m_lFanList.push_back(53);

		//三风刻
		if (IsSanFengKe(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(46);
		}
	}
	//三风刻
	else if (IsSanFengKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(46);
	}
	//三色三节高
	else if (IsSanSeSanJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(38);
	}

	KeZiFan_3Part();
}

//刻子番型
void CCardFan::KeZiFan_3Part()
{
	//小三元
	if (IsXiaoSanYuan(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(69);
		m_bJianKe = false;
		m_bYaoJiuKe = false;
	}
	//双箭刻
	else if (IsShuangJianKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(33);
		m_bYaoJiuKe = false;

		//双暗刻
		if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
		{
			m_lFanList.push_back(22);
		}
	}
	//双同刻
	else if (IsShuangTongKe(m_bKeZi,m_bKeZiNum) && m_bShuangTongKe)
	{
		m_lFanList.push_back(23);

		//双暗刻
		if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
		{
			m_lFanList.push_back(22);
		}
	}
	//双暗刻
	else if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
	{
		m_lFanList.push_back(22);
	}
}

//刻子番型
void CCardFan::KeZiFan_4Part()
{
	//声明变量
	BYTE bYaoJiuKe = IsYaoJiuKe(m_bKeZi,m_bKeZiNum);
	BYTE bSanFenKe = IsSanFengKe(m_bKeZi,m_bKeZiNum);

	//门风刻
	if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)) && m_bMenQuanFeng)
	{
		m_lFanList.push_back(16);

		//圈风刻
		if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)) && m_bMenQuanFeng)
		{
			m_lFanList.push_back(15);

			//箭刻
			if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
			{
				m_lFanList.push_back(14);

				//幺九刻
				if ((bYaoJiuKe) && (m_bYaoJiuKe))
				{
					if (m_HeItem.cbMenFeng == m_HeItem.cbQuanFeng)
					{
						if (bSanFenKe)
						{
							bYaoJiuKe -= 4;
						}
						else 
						{
							bYaoJiuKe -= 2;
						}
						for (BYTE i = 0; i < bYaoJiuKe; i++)
						{
							m_lFanList.push_back(6);
						}
					}
					else 
					{
						if (bSanFenKe)
						{
							bYaoJiuKe -= 4;
						}
						else 
						{
							bYaoJiuKe -= 3;
						}
						for (BYTE i = 0; i < bYaoJiuKe; i++)
						{
							m_lFanList.push_back(6);
						}
					}
				}
			}
			//幺九刻
			else if ((bYaoJiuKe) && (m_bYaoJiuKe))
			{
				if (m_HeItem.cbMenFeng == m_HeItem.cbQuanFeng)
				{
					if (bSanFenKe)
					{
						bYaoJiuKe -= 3;
					}
					else 
					{
						bYaoJiuKe -= 1;
					}
					for (BYTE i = 0; i < bYaoJiuKe; i++)
					{
						m_lFanList.push_back(6);
					}
				}
				else 
				{
					if (bSanFenKe)
					{
						bYaoJiuKe -= 3;
					}
					else 
					{
						bYaoJiuKe -= 2;
					}
					for (BYTE i = 0; i < bYaoJiuKe; i++)
					{
						m_lFanList.push_back(6);
					}
				}
			}
		}
		//箭刻
		else if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
		{
			m_lFanList.push_back(14);

			//幺九刻
			if (bYaoJiuKe)
			{
				if (bSanFenKe)
				{
					bYaoJiuKe -= 4;
				}
				else 
				{
					bYaoJiuKe -= 2;
				}
				for (BYTE i = 0; i < bYaoJiuKe; i++)
				{
					::AfxMessageBox("幺九刻");
					m_lFanList.push_back(6);
				}
			}
		}
		//幺九刻
		else if ((bYaoJiuKe) && (m_bYaoJiuKe))
		{
			if (bSanFenKe)
			{
				bYaoJiuKe -= 3;
			}
			else 
			{
				bYaoJiuKe -= 1;
			}
			for (BYTE i = 0; i < bYaoJiuKe; i++)
			{
				m_lFanList.push_back(6);
			}
		}
	}
	//圈风刻
	else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)) && (m_bMenQuanFeng))
	{
		m_lFanList.push_back(15);

		//箭刻
		if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
		{
			::AfxMessageBox("箭刻");
			m_lFanList.push_back(14);

			//幺九刻
			if ((bYaoJiuKe) && (m_bYaoJiuKe))
			{
				if (bSanFenKe)
				{
					bYaoJiuKe -= 4;
				}
				else 
				{
					bYaoJiuKe -= 2;
				}
				for (BYTE i = 0; i < bYaoJiuKe - 2; i++)
				{
					m_lFanList.push_back(6);
				}
			}
		}
		//幺九刻
		else if ((bYaoJiuKe) && (m_bYaoJiuKe))
		{
			if (bSanFenKe)
			{
				bYaoJiuKe -= 3;
			}
			else 
			{
				bYaoJiuKe -= 1;
			}
			for (BYTE i = 0; i < bYaoJiuKe; i++)
			{
				m_lFanList.push_back(6);
			}
		}
	}
	//箭刻
	else if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
	{
		m_lFanList.push_back(14);

		//幺九刻
		if ((bYaoJiuKe) && (m_bYaoJiuKe))
		{
			if (bSanFenKe)
			{
				bYaoJiuKe -= 4;
			}
			else 
			{
				bYaoJiuKe -= 1;
			}
			for (BYTE i = 0; i < bYaoJiuKe; i++)
			{
				m_lFanList.push_back(6);
			}
		}
	}
	//幺九刻
	else if ((bYaoJiuKe) && (m_bYaoJiuKe))
	{
		if (bSanFenKe)
		{
			bYaoJiuKe -= 3;
		}
		for (BYTE i = 0; i < bYaoJiuKe; i++)
		{
			m_lFanList.push_back(6);
		}
	}
}

//顺子番型
void CCardFan::ShunZiFan()
{
	if (m_bShunZiNum == 4)
	{
		ShunZiFan_1Part();
	}
	else if (m_bShunZiNum == 3)
	{
		ShunZiFan_2Part();
	}
	else if (m_bShunZiNum == 2)
	{
		ShunZiFan_3Part();
	}
}

//顺子番型
void CCardFan::ShunZiFan_1Part()
{
	//一色双龙会
	if (IsYiSeShuangLongHui(m_bShunZi,m_bShunZiNum,m_bJiang))
	{
		m_lFanList.push_back(72);
		m_bQingYiSe = false;
		m_bPingHe = false;
		m_bWuZi = false;
	}
	//一色四同顺
	else if (IsYiSeSiTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(68);
		m_bSiGuiYi = false;
	}
	//一色四步高
	else if (IsYiSeSiBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(65);

		//老少副
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);
		}
		//连六
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
	}
	//一色三同顺
	else if (IsYiSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(60);

		ShunZiFan_3Part();
	}
	//三色双龙会
	else if (IsSanSeShuangLongHui(m_bShunZi,m_bShunZiNum,m_bJiang))
	{
		m_lFanList.push_back(52);
		m_bPingHe = false;
		m_bWuZi = false;
	}
	//一色三步高
	else if (IsYiSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(50);

		ShunZiFan_3Part();
	}
	//清龙
	else if (IsQingLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(49);

		//喜相逢
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//三色三同顺
	else if (IsSanSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(36);

		//老少副
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);
		}
		//连六
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//花龙
	else if (IsHuaLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(35);

		//老少副
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);

			//连六
			if (IsLianLiu(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(3);
			}
			//喜相逢
			else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//一般高
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//连六
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);

			//喜相逢
			if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//一般高
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//喜相逢
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//一般高
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//三色三步高
	else if (IsSanSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(30);

		ShunZiFan_3Part();
	}
	//老少副
	else if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);

		//连六
		if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);

			//喜相逢
			if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//一般高
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//喜相逢
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//一般高
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//连六
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);

		//喜相逢
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//一般高
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//喜相逢
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);

		//一般高
		if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//一般高
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//顺子番型
void CCardFan::ShunZiFan_2Part()
{
	//一色三同顺
	if (IsYiSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(60);
	}
	//一色三步高
	else if (IsYiSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(50);
	}
	//清龙
	else if (IsQingLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(49);
	}
	//三色三同顺
	else if (IsSanSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(36);
	}
	//花龙
	else if (IsHuaLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(35);
	}
	//三色三步高
	else if (IsSanSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(30);
	}
	//老少副
	else if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);

		//连六
		if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
		//喜相逢
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//连六
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);

		//喜相逢
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//一般高
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//喜相逢
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);

		//一般高
		if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//一般高
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//顺子番型
void CCardFan::ShunZiFan_3Part()
{
	//老少副
	if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);
	}
	//连六
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);
	}
	//喜相逢
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);
	}
	//一般高
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//杠牌番型
void CCardFan::GangFan()
{
	if (m_bGangNum == 4)      //四个杠
	{
		//四杠
		if (IsSiGang(m_bGangNum))
		{
			m_lFanList.push_back(80);
			m_bDanDiaoJiang = false;
			m_bPengPengHe = false;
		}
	}
	else if (m_bGangNum == 3) //三个杠
	{
		//三杠
		if (IsSanGang(m_bGangNum))
		{
			m_lFanList.push_back(66);
		}
	}
	else if (m_bGangNum == 2) //俩个杠
	{
		//双暗杠
		if (IsShuangAnGang(m_bAnGangNum))
		{
			m_lFanList.push_back(34);
			m_bShuangAnKe = false;
		}
		//双明杠
		if (IsShuangMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(26);
		}
	}
	else if (m_bGangNum == 1) //一个杠
	{

		if (IsAnGang(m_bAnGangNum)) 
		{
			m_lFanList.push_back(21);
		}
		//明杠
		else if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
}

//其他番型
void CCardFan::QiTaFan()
{
	QiTaFan_1Part();
	QiTaFan_2Part();
	QiTaFan_3Part();
	QiTaFan_4Part();
	QiTaFan_5Part();
}

//其他番型
void CCardFan::QiTaFan_1Part()
{
	//九宝莲灯
	if (IsJiuBaoLianDeng(m_bAllCard,m_bChiNum,m_bMingKeNum,m_bGangNum))
	{
		m_lFanList.push_back(79);
		m_bBuMen = false;
		m_bWuZi = false;
	}
	//绿一色
	else if (IsLuYiSe(m_bAllCard))
	{
		m_lFanList.push_back(78);

		//清一色
		if (IsQingYiSe(m_bAllCard) && m_bQingYiSe)
		{
			m_lFanList.push_back(55);
			m_bWuZi = false;
		}
	}
	//全小
	else if (IsQuanXiao(m_bAllCard))
	{
		m_lFanList.push_back(63);
		m_bWuZi = false;
	}
	//全中
	else if (IsQuanZhong(m_bAllCard))
	{
		m_lFanList.push_back(62);
		m_bDuanYao = false;

		//全带五
		if(IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))
		{
			m_lFanList.push_back(51);
		}
	}
	//全大
	else if (IsQuanDa(m_bAllCard))
	{
		m_lFanList.push_back(61);
		m_bWuZi = false;
	}
	//清一色
	else if(IsQingYiSe(m_bAllCard) && m_bQingYiSe)
	{
		m_lFanList.push_back(55);
		m_bWuZi = false;

		//大于五
		if (IsDaYuWu(m_bAllCard))
		{
			m_lFanList.push_back(48);

			//碰碰和
			if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
			{
				m_lFanList.push_back(28);
			}
		}
		//小于五
		else if (IsXiaoYuWu(m_bAllCard))
		{
			m_lFanList.push_back(47);

			//碰碰和
			if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
			{
				m_lFanList.push_back(28);
			}
		}
		//碰碰和
		else if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
		{
			m_lFanList.push_back(28);
		}
	}
	//全带五
	else if(IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(51);
		m_bDuanYao = false;
	}
	//大于五
	else if (IsDaYuWu(m_bAllCard))
	{
		m_lFanList.push_back(48);
		m_bWuZi = false;
	}
	//小于五
	else if (IsXiaoYuWu(m_bAllCard))
	{
		m_lFanList.push_back(47);
		m_bWuZi = false;
	}
	//混一色
	else if (IsHunYiSe(m_bAllCard))
	{
		m_lFanList.push_back(29);
		
		//碰碰和
		if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
		{
			m_lFanList.push_back(28);
		}
	}
	//碰碰和
	else if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
	{
		m_lFanList.push_back(28);
	}
}

//其他番型
void CCardFan::QiTaFan_2Part()
{
	//妙手回春
	if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
	{
		m_lFanList.push_back(42);
		m_bZiMo = false; 

		//杠上开花
		if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
		{
			m_lFanList.push_back(40);
		}
	}
	//海底捞月
	else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
	{
		m_lFanList.push_back(41);

		//抢杠和
		if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
	}
	//杠上开花
	else if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
	{
		m_lFanList.push_back(40);
		m_bZiMo = false;
	}
	//抢杠和
	else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
	{
		m_lFanList.push_back(39);
        m_bHeJueZhang = false;
	}
}

//其他番型
void CCardFan::QiTaFan_3Part()
{
	//声明变量
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);
	
	//推不到
	if (IsTuiBuDao(m_bAllCard))
	{
		m_lFanList.push_back(37);

		//全求人
		if (IsQuanQiuRen(m_HeItem.bZiMo,bHeYiZhang,m_HeItem.bHeCard,m_bJiang,m_bChiNum,m_bMingKeNum,m_bMingGangNum))
		{
			m_lFanList.push_back(32);
			m_bDanDiaoJiang = false;
		}
		//不求人
		else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
			{
				m_lFanList.push_back(27);
			}
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
		{
			m_lFanList.push_back(27);

			//门前清
			if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(17);
			}
			//自摸
			else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
			{
				m_lFanList.push_back(12);
			}
		}
		//门前清
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);
		}
	}
	//全求人
	else if (IsQuanQiuRen(m_HeItem.bZiMo,bHeYiZhang,m_HeItem.bHeCard,m_bJiang,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(32);
		m_bDanDiaoJiang = false;

		//五门齐
		if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
		//缺一门
		else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//五门齐
	else if (IsWuMenQi(m_bAllCard))
	{
		m_lFanList.push_back(31);

		//不求人
		if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
			{
				m_lFanList.push_back(27);
			}
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
		{
			m_lFanList.push_back(27);

			//门前清
			if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(17);
			}
			//自摸
			else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
			{
				m_lFanList.push_back(12);
			}
		}
		//门前清
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);
		}
	}
	//和绝张
	else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
	{
		m_lFanList.push_back(27);

		//不求人
		if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//缺一门
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//门前清
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);

			//缺一门
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);

			//缺一门
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//缺一门
		else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//不求人
	else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(24);

		//缺一门
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//门前清
	else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(17);

		//缺一门
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//自摸
	else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
	{
		m_lFanList.push_back(12);

		//缺一门
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//缺一门
	else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen) 
	{
		m_lFanList.push_back(4);
	}
}

//其他番型
void CCardFan::QiTaFan_4Part()
{
	//声明变量
	BYTE bSiGuiYi = IsSiGuiYi(m_bHandCardIndex);

	//全带幺
	if (IsQuanDaiYao(m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bGang,m_bGangNum,m_bJiang) && m_bQuanDaiYao)
	{
		m_lFanList.push_back(25);

		//四归一
		if (bSiGuiYi && m_bSiGuiYi)
		{
			for (BYTE i = 0; i < bSiGuiYi; i++)
			{
				m_lFanList.push_back(20);
			}
		}
	}
	//四归一
	else if (bSiGuiYi && m_bSiGuiYi)
	{
		for (BYTE i = 0; i < bSiGuiYi; i++)
		{
			m_lFanList.push_back(20);
		}

		//断幺
		if ((IsDuanYao(m_bAllCard)) && (m_bDuanYao))
		{
			m_lFanList.push_back(19);
		}
		//无字
		else if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//断幺
	else if ((IsDuanYao(m_bAllCard)) && (m_bDuanYao))
	{
		m_lFanList.push_back(19);
	}
	//无字
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);
	}
}

//其他番型
void CCardFan::QiTaFan_5Part()
{
	//声明变量
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);
	
	//平和
	if (IsPingHe(m_bShunZiNum,m_bJiang) && m_bPingHe)
	{
		m_lFanList.push_back(18);

		//单钓将
		if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang) && m_bDanDiaoJiang)
		{
			m_lFanList.push_back(11);
		}
		//坎张
		else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(10);
		}
		//边张
		else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(9);
		}
	}
	//单钓将
	else if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang) && m_bDanDiaoJiang)
	{
		m_lFanList.push_back(11);
	}
	//坎张
	else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(10);
	}
	//边张
	else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(9);
	}
}

//七对翻型
void CCardFan::QiDuiFan()
{
	QiDuiFan_1Part();
	QiDuiFan_2Part();
	QiDuiFan_3Part();
}

//七对翻型
void CCardFan::QiDuiFan_1Part()
{
	//声明变量
	BOOL bQiDui = true;
	
	//连七对
	if (IsLianQiDui(bQiDui,m_bCardIndex))
	{
		m_lFanList.push_back(81);
		m_bWuZi = false;
	}
	//七对
	else if (IsQiDui(bQiDui))
	{
		m_lFanList.push_back(56);

		//绿一色
		if (IsLuYiSe(m_bAllCard))
		{
			m_lFanList.push_back(78);

			//清一色
			if (IsQingYiSe(m_bAllCard))
			{
				m_lFanList.push_back(55);
				m_bWuZi = false;
			}
		}
		//清幺九
		else if (IsQingYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(74);
			m_bWuZi = false;
		}
		//字一色
		else if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bWuZi = false;
		}
		//混幺九
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bWuZi = false;
		}
		//清一色
		else if (IsQingYiSe(m_bAllCard) && m_bQingYiSe)
		{
			m_lFanList.push_back(55);
			m_bWuZi = false;

			//大于五
			if (IsDaYuWu(m_bAllCard))
			{
				m_lFanList.push_back(48);
				m_bWuZi = false;
			}
			//小于五
			else if (IsXiaoYuWu(m_bAllCard))
			{
				m_lFanList.push_back(47);
				m_bWuZi = false;
			}
		}
		//全小
		else if (IsQuanXiao(m_bAllCard))
		{
			m_lFanList.push_back(63);
			m_bWuZi = false;
		}
		//全中
		else if (IsQuanZhong(m_bAllCard))
		{
			m_lFanList.push_back(62);
			m_bDuanYao = false;
		}
		//全大
		else if (IsQuanDa(m_bAllCard))
		{
			m_lFanList.push_back(61);
			m_bWuZi = false;
		}
		//大于五
		else if (IsDaYuWu(m_bAllCard))
		{
			m_lFanList.push_back(48);
			m_bWuZi = false;
		}
		//小于五
		else if (IsXiaoYuWu(m_bAllCard))
		{
			m_lFanList.push_back(47);
			m_bWuZi = false;
		}
		//混一色
		else if (IsHunYiSe(m_bAllCard))
		{
			m_lFanList.push_back(29);
		}		
	}
}

//七对翻型
void CCardFan::QiDuiFan_2Part()
{
	//妙手回春
	if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
	{
		m_lFanList.push_back(42);

		//推不到
		if (IsTuiBuDao(m_bAllCard))
		{
			m_lFanList.push_back(37);
		}
		//五门齐
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
	}
	//海底捞月
	else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
	{
		m_lFanList.push_back(41);

		//推不到
		if (IsTuiBuDao(m_bAllCard))
		{
			m_lFanList.push_back(37);
		}
		//五门齐
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
	}
	//推不到
	if (IsTuiBuDao(m_bAllCard))
	{
		m_lFanList.push_back(37);

		//自摸
		if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
	//五门齐
	else if (IsWuMenQi(m_bAllCard))
	{
		m_lFanList.push_back(31);

		//自摸
		if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
	//自摸
	else if (IsZiMo(m_HeItem.bZiMo))
	{
		m_lFanList.push_back(12);
	}
}

//七对翻型
void CCardFan::QiDuiFan_3Part()
{
	//声明变量
	BYTE bSiGuiYi = IsSiGuiYi(m_bHandCardIndex);
	
	//四归一
	if (bSiGuiYi)
	{
		for (BYTE i = 0; i < bSiGuiYi; i++)
		{
			m_lFanList.push_back(20);
		}

		//断幺
		if ((IsDuanYao(m_bAllCard)))
		{
			m_lFanList.push_back(19);

			//缺一门
			if (IsQueYiMen(m_bAllCard))
			{
				m_lFanList.push_back(4);
			}
		}
		//无字
		else if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);

			//缺一门
			if (IsQueYiMen(m_bAllCard))
			{
				m_lFanList.push_back(4);
			}
		}
		//缺一门
		else if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//断幺
	else if ((IsDuanYao(m_bAllCard)))
	{
		m_lFanList.push_back(19);

		//缺一门
		if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//无字
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);

		//缺一门
		if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//缺一门
	else if (IsQueYiMen(m_bAllCard))
	{
		m_lFanList.push_back(4);
	}
}

//十三幺
void CCardFan::ShiSanYaoFan()
{
	//声明变量
	BOOL bShiSanYao = true;
	
	//十三幺
	if (IsShiSanYao(bShiSanYao))
	{
		::AfxMessageBox("十三幺");

		//妙手回春
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			::AfxMessageBox("妙手回春");

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				::AfxMessageBox("和绝张");
			}
		}
		//海底捞月
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			::AfxMessageBox("海底捞月");

			//抢杠和
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				::AfxMessageBox("抢杠和");
			}
		}
		//抢杠和
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			::AfxMessageBox("抢杠和");
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			::AfxMessageBox("和绝张");

			//自摸
			if (IsZiMo(m_HeItem.bZiMo))
			{
				::AfxMessageBox("自摸");
			}
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			::AfxMessageBox("自摸");
		}
	}
}

//七星不靠番型
void CCardFan::QiXingBuKaoFan()
{
	//声明变量
	BOOL bQiXingBuKao = true;
	
	//七星不靠
	if (IsQiXingBuKao(bQiXingBuKao))
	{
		m_lFanList.push_back(57);

		//妙手回春
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);
			}
		}
		//海底捞月
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//抢杠和
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);
			}
		}
		//抢杠和
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//自摸
			if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//组合龙番型
void CCardFan::ZuHeLongFan()
{
	ZuHeLongFan_1Part();
	ZuHeLongFan_2Part();
	ZuHeLongFan_3Part();
}

//组合龙番型
void CCardFan::ZuHeLongFan_1Part()
{
	//声明变量
	BOOL bZuHeLong = true;
	
	//组合龙
	if (IsZuHeLong(bZuHeLong))
	{
		m_lFanList.push_back(45);
		
		//妙手回春
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//杠上开花
			if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
			{
				m_lFanList.push_back(40);

				//五门齐
				if (IsWuMenQi(m_bAllCard))
				{
					m_lFanList.push_back(31);

					//和绝张
					if (IsHeJueZhang(m_HeItem.bHeJueZhang))
					{
						m_lFanList.push_back(27);

						//不求人
						if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
						{
							m_lFanList.push_back(24);
						}
					}
					//不求人
					else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//和绝张
				else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//不求人
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//不求人
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//五门齐
			else if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//和绝张
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//不求人
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//不求人
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//和绝张
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//不求人
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//不求人
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
		}
		//海底捞月
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//抢杠和
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);

				//五门齐
				if (IsWuMenQi(m_bAllCard))
				{
					m_lFanList.push_back(31);

					//门前清
					if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
					{
						m_lFanList.push_back(17);
					}
				}
				//门前清
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//五门齐
			else if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//和绝张
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//门前清
					if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
					{
						m_lFanList.push_back(17);
					}
				}
				//门前清
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//和绝张
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//门前清
				if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//门前清
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
		}
		//杠上开花
		else if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
		{
			m_lFanList.push_back(40);

			//五门齐
			if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//和绝张
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//不求人
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//不求人
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//和绝张
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//不求人
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//不求人
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
		}
		//抢杠和
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);

			//五门齐
			if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//门前清
				if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//门前清
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
		}
		//五门齐
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//不求人
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
				//门前清
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
				//自摸
				else if (IsZiMo(m_HeItem.bZiMo))
				{
					m_lFanList.push_back(12);
				}
			}
			//不求人
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
			//门前清
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
			//自摸
			else if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//不求人
			if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
			//门前清
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
			//自摸
			else if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//不求人
		else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);
		}
		//门前清
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
		{
			m_lFanList.push_back(17);
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//组合龙番型
void CCardFan::ZuHeLongFan_2Part()
{
	//暗杠
	if (IsAnGang(m_bAnGangNum)) 
	{
		m_lFanList.push_back(21);
		
		//门风刻
		if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(16);
			
			//圈风刻
			if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
			{
				m_lFanList.push_back(15);
			}
		}
		//圈风刻
		else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(15);
		}
		//箭刻
		else if (IsJianKe(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(14);
		}
		//幺九刻
		else if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
		{
			m_lFanList.push_back(6);
		}
	}
	//门风刻
	else if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)))
	{
		m_lFanList.push_back(16);

		//圈风刻
		if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(15);

			//明杠
			if (IsMingGang(m_bMingGangNum))
			{
				m_lFanList.push_back(8);
			}
		}
		//明杠
		else if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//圈风刻
	else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
	{
		m_lFanList.push_back(15);

		//明杠
		if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//箭刻
	else if (IsJianKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(14);

		//明杠
		if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//明杠
	else if (IsMingGang(m_bMingGangNum))
	{
		m_lFanList.push_back(8);

		//幺九刻
		if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
		{
			m_lFanList.push_back(6);
		}
	}
	//幺九刻
	else if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
	{
		m_lFanList.push_back(6);
	}
}

//组合龙番型
void CCardFan::ZuHeLongFan_3Part()
{
	//声明变量
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);

	//单钓将
	if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang))
	{
		m_lFanList.push_back(11);

		//无字
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//坎张
	else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(10);

		//无字
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//边张
	else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(9);

		//无字
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//无字
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);
	}
}

//全不靠番型
void CCardFan::QuanBuKaoFan()
{
	//声明变量
	BOOL bQuanBuKao = true;
	
	//全不靠
	if (IsQuanBuKao(bQuanBuKao))
	{
		m_lFanList.push_back(44);

		//妙手回春
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//和绝张
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);
			}
		}
		//海底捞月
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//抢杠和
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);
			}
		}
		//抢杠和
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
		//和绝张
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//自摸
			if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//自摸
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//1番

//一般高
bool CCardFan::IsYiBanGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 2)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = i + 1; j < bShunZiNum; j++)
		{
			if (bShunZi[i] == bShunZi[j])
			{
				return true;
			}
		}
	}

	return false;
}

//喜相逢
bool CCardFan::IsXiXiangFeng(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 2)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = i + 1; j < bShunZiNum; j++)
		{
			if ((bShunZi[i] != bShunZi[j]) && (bShunZi[i] % 9 == bShunZi[j] % 9))
			{
				return true;
			}
		}
	}

	return false;
}

//连六
bool CCardFan::IsLianLiu(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 2)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			if (i != j)
			{
				if ((bShunZi[i] == bShunZi[j] - 3) && (bShunZi[i] % 9 == bShunZi[j] % 9 - 3))
				{
					return true;
				}
			}
		}
	}

	return false;
}

//老少副
bool CCardFan::IsLaoShaoFu(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 2)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			if (i != j)
			{
				if ((bShunZi[i] == bShunZi[j] + 6) && (bShunZi[i] % 9 == bShunZi[j] % 9 + 6))
				{
					return true;
				}
			}
		}
	}

	return false;
}

//幺九刻
BYTE CCardFan::IsYaoJiuKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//声明变量
	BYTE bYaoJiuNum = 0;

	//循环检测
	for (BYTE i =0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] % 9 == 0) || (bKeZi[i] % 9 == 8) || (bKeZi[i] > 26))
		{
			bYaoJiuNum++;
		}
	}

	return bYaoJiuNum;
}

//明杠
BYTE CCardFan::IsMingGang(BYTE bMingGanNum)
{
	return bMingGanNum;
}

//缺一门
bool CCardFan::IsQueYiMen(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bCardColor[3] = {0,0,0};
	BYTE bColorNum = 0;

	//颜色判断
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] >= 0) && (bAllCard[i] <= 8))
		{
			bCardColor[0] = 1;
		}
		if ((bAllCard[i] >= 9) && (bAllCard[i] <= 17))
		{
			bCardColor[1] = 1;
		}
		if ((bAllCard[i] >= 18) && (bAllCard[i] <= 26))
		{
			bCardColor[2] = 1;
		}
	}

	//颜色统计
	for (BYTE n = 0; n < 3; n++)
	{
		bColorNum += bCardColor[n];
	}

	return ((bColorNum == 2) ? true : false);
}

//无字
bool CCardFan::IsWuZi(BYTE bAllCard[MAX_COUNT])
{
	//循环检测
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//边张
bool CCardFan::IsBianZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunZi[4], BYTE bShunZiNum)
{
	if (bHeYiZhang)
	{
		for (BYTE i = 0; i < bShunZiNum; i++)
		{
			if (((bHeCard == bShunZi[i]) && ( bShunZi[i] % 9 == 6)) || ((bHeCard == bShunZi[i] + 2) && ( (bShunZi[i] + 2) % 9 == 2)))
			{
				return true;
			}
		}
	}

	return false;
}

//坎张
bool CCardFan::IsKanZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunZi[4], BYTE bShunZiNum)
{
	if (bHeYiZhang)
	{
		for (BYTE i = 0; i < bShunZiNum; i++)
		{
			if (bHeCard == bShunZi[i] + 1)
			{
				return true;
			}
		}
	}

	return false;
}

//单钓将
bool CCardFan::IsDanDiaoJiang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bJiang)
{
	if (bHeYiZhang && (bHeCard == bJiang))
	{
		return true;
	}

	return false;
}

//自摸
bool CCardFan::IsZiMo(BOOL bZiMo)
{
	return (bZiMo ? true : false);
}

//花牌
BYTE CCardFan::IsHuaPai(BYTE bHuaNum)
{
	return bHuaNum;
}

//2番

//箭刻
BOOL CCardFan::IsJianKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//声明变量
	BYTE bJanKeNum = 0;

	//循环检测
	for (BYTE i =0; i< bKeZiNum; i++)
	{
		if ((bKeZi[i] >= 31) && (bKeZi[i] <= 33))
		{
			bJanKeNum++;
		}
	}

	return ((bJanKeNum == 1) ? true : false);
}

//圈风刻
bool CCardFan::IsQuanFengKe(BYTE bQuanFeng, BYTE bKeZi[4], BYTE bKeZiNum)
{
	//循环检测
	for (BYTE i =0; i < bKeZiNum; i++)
	{
		if (bKeZi[i] == bQuanFeng)
		{
			return true;
		}
	}

	return false;
}

//门风刻
bool CCardFan::IsMenFengKe(BYTE bMenFeng, BYTE bKeZi[4], BYTE bKeZiNum)
{
	//循环检测
	for (BYTE i =0; i< bKeZiNum; i++)
	{
		if (bKeZi[i] == bMenFeng)
		{
			return true;
		}
	}

	return false;
}

//门前清
bool CCardFan::IsMenQianQing(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum)
{
	if (!bZiMo && (bMingKeZiNum == 0) && (bChiNum == 0)&& (bMingGangNum ==0))
	{
		return true;
	}

	return false;
}

//平和 
bool CCardFan::IsPingHe(BYTE bShunZiNum, BYTE bJiang)
{
	if ((bShunZiNum == 4) && (bJiang < 27))
	{
		return true;
	}

	return false;
}

//四归一
BYTE CCardFan::IsSiGuiYi(BYTE bCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bSiGuiYiNum = 0;

	//循环检测
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (bCardIndex[i] == 4)
		{
			bSiGuiYiNum++;
		}
	}

	return bSiGuiYiNum ;
}

//双同刻
bool CCardFan::IsShuangTongKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//条件判断
	if (bKeZiNum > 1)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		for (BYTE j = i + 1; j < bKeZiNum; j++)
		{
			if ((bKeZi[i] % 9 == bKeZi[j] % 9) && (bKeZi[i] < 27) && (bKeZi[j] < 27))
			{
				return true;
			}
		}
	}

	return false;
}

//双暗刻
bool CCardFan::IsShuangAnKe(BYTE bAnKeNum)
{
	return ((bAnKeNum == 2) ? true : false);
}

//暗杠 
BYTE CCardFan::IsAnGang(BYTE bAnGangNum)
{
	return bAnGangNum;
}

//断幺 
bool CCardFan::IsDuanYao(BYTE bAllCard[MAX_COUNT])
{
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if (((bAllCard[i] >= 27) && (bAllCard[i] <= 33)) || (bAllCard[i] % 9 == 0) || (bAllCard[i] % 9 == 8))
		{
			return false;
		}
	}

	return true;
}

//4番

//全带幺
bool CCardFan::IsQuanDaiYao(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum, BYTE bGang[4], BYTE bGangNum, BYTE bJiang)
{
	//检测顺子
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		if ((bShunZi[i] % 9 != 0) && (bShunZi[i] % 9 != 6)) 
		{
			return false;
		}
	}

	//检测刻子
	for (BYTE j = 0; j < bKeZiNum; j++)
	{
		if ((bKeZi[j] % 9 != 0) && (bKeZi[j] % 9 != 8)) 
		{
			return false;
		}
	}

	//检测杠牌
	for (BYTE n = 0; n < bGangNum; n++)
	{
		if ((bGang[n] % 9 != 0) && (bGang[n] % 9 != 8)) 
		{
			return false;
		}
	}

	//检测将牌
	if (((bJiang % 9 != 0) && (bJiang % 9 != 8) && (bJiang < 27))) 
	{
		return false;
	}

	return true;
}

//不求人
bool CCardFan::IsBuQiuRen(BOOL bZiMo,BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum)
{
	if (bZiMo && (bMingKeZiNum == 0) && (bChiNum == 0) && (bMingGangNum == 0))
	{
		return true;
	}

	return false;
}

//双明杠
bool CCardFan::IsShuangMingGang(BYTE bMingGangNum)
{
	return ((bMingGangNum == 2) ? true : false);
}

//和绝张
bool CCardFan::IsHeJueZhang(BOOL bJueZhang)
{
	return (bJueZhang ? true : false);
}

//6 番

//碰碰和
bool CCardFan::IsPengPengHe(BYTE bKeZiNum, BYTE bGangNum)
{
	//声明变量
	BYTE bPengPeng = bKeZiNum + bGangNum;
	
	if (bGangNum != 0)
	{
		bPengPeng -= bGangNum;
	}
	return ((bPengPeng == 4) ? true : false);
}

//混一色
bool CCardFan::IsHunYiSe(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bCardColor[4] = {0,0,0,0};
	BYTE bColorNum = 0;

	//颜色判断
	for (BYTE i = 0; i< 14; i++)
	{
		if ((bAllCard[i] >= 0) && (bAllCard[i] <= 8))
		{
			bCardColor[0] = 1;
		}
		if ((bAllCard[i] >= 9) && (bAllCard[i] <= 17))
		{
			bCardColor[1] = 1;
		}
		if ((bAllCard[i] >= 18) && (bAllCard[i] <= 26))
		{
			bCardColor[2] = 1;
		}
		if ((bAllCard[i] >= 27) && (bAllCard[i] <= 33))
		{
			bCardColor[3] = 1;
		}
	}

	//颜色统计
	for (BYTE n = 0; n < 3; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return (((bColorNum == 1) && (bCardColor[3] == 1)) ? true : false);
}

//三色三步高
bool CCardFan::IsSanSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			for (BYTE n = 0; n < bShunZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if (((bShunZi[i] % 9 == bShunZi[j] % 9 - 1) && (bShunZi[i] % 9 == bShunZi[n] % 9 - 2)) &&
						((bShunZi[i]!= bShunZi[j] - 1) && (bShunZi[i]!= bShunZi[n] - 2) && (bShunZi[j] != bShunZi[n] - 1)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//五门齐
bool CCardFan::IsWuMenQi(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bCardColor[5] = {0,0,0,0,0};
	BYTE bColorNum = 0;

	//颜色判断
	for (BYTE i = 0; i< 14; i++)
	{
		if ((bAllCard[i] >= 0) && (bAllCard[i] <= 8))
		{
			bCardColor[0] = 1;
		}
		if ((bAllCard[i] >= 9) && (bAllCard[i] <= 17))
		{
			bCardColor[1] = 1;
		}
		if ((bAllCard[i] >= 18) && (bAllCard[i] <= 26))
		{
			bCardColor[2] = 1;
		}
		if ((bAllCard[i] >= 27) && (bAllCard[i] <= 30))
		{
			bCardColor[3] = 1;
		}
		if ((bAllCard[i] >= 31) && (bAllCard[i] <= 33))
		{
			bCardColor[4] = 1;
		}
	}

	//颜色统计
	for (BYTE n = 0; n < 5; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return ((bColorNum == 5) ? true : false);
}

//全求人
bool CCardFan::IsQuanQiuRen(BOOL bZiMo, BOOL bHeYiZhang, BYTE bHeCard, BYTE bJiang, BYTE bChiNum, BYTE bMingKeZiNum,BYTE bMingGangNum)
{
	//声明变量
	BYTE bCardNum = bChiNum + bMingKeZiNum + bMingGangNum;
	if (!bZiMo && (bHeYiZhang) && (bHeCard == bJiang) && (bCardNum == 4))
	{
		return true;
	}

	return false;
}

//双暗杠
bool CCardFan::IsShuangAnGang(BYTE bAnGangNum)
{
	return ((bAnGangNum == 2) ? true : false);
}

//双箭刻
bool CCardFan::IsShuangJianKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//声明变量
	BYTE bJanKeNum = 0;

	for (BYTE i =0; i<bKeZiNum; i++)
	{
		if ((bKeZi[i] >= 31) && (bKeZi[i] <= 33))
		{
			bJanKeNum++;
		}
	}

	return ((bJanKeNum == 2) ? true : false);
}

//8番

//花龙
bool CCardFan::IsHuaLong(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			for (BYTE n = 0; n < bShunZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if (((bShunZi[i] % 9 == bShunZi[j] % 9 - 3) && (bShunZi[i] % 9 == bShunZi[n] % 9 - 6)) &&
						((bShunZi[i]!= bShunZi[j] - 3) && (bShunZi[i]!= bShunZi[n] - 6) && (bShunZi[j] != bShunZi[n] - 3)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//推不倒 
bool CCardFan::IsTuiBuDao(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bTuiBuDao[14] = {9,10,11,12,13,16,17,19,21,22,23,25,26,33};
	BYTE bTuiBudaoNum = 0;

	for (BYTE i = 0; i < MAX_COUNT; i++)
	{
		for (BYTE j = 0; j < 14; j++)
		{
			if (bAllCard[i] == bTuiBuDao[j])
			{
				bTuiBudaoNum ++;
				break;
			}
		}
	}

	return ((bTuiBudaoNum == 14) ? true : false);
}

//三色三同顺
bool CCardFan::IsSanSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = i + 1; j < bShunZiNum; j++)
		{
			for (BYTE n = j + 1; n < bShunZiNum; n++)
			{
				if (((bShunZi[i] % 9 == bShunZi[j] % 9) && (bShunZi[i] % 9 == bShunZi[n] % 9)) &&
					((bShunZi[i]!= bShunZi[j]) && (bShunZi[i]!= bShunZi[n]) && (bShunZi[j] != bShunZi[n])))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//三色三节高
bool CCardFan::IsSanSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//条件判断
	if (bKeZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		for (BYTE j = 0; j < bKeZiNum; j++)
		{
			for (BYTE n = 0; n < bKeZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if (((bKeZi[i] % 9 == bKeZi[j] % 9 - 1) && (bKeZi[i] % 9 == bKeZi[n] % 9 - 2)) &&
						((bKeZi[i]!= bKeZi[j] - 1) && (bKeZi[i]!= bKeZi[n] - 2) && (bKeZi[j] != bKeZi[n] - 1)) &&
						((bKeZi[i] < 27) && (bKeZi[j] < 27) && (bKeZi[n] < 27)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//无番和
bool CCardFan::IsWuFanHe(BOOL bWuFan)
{
	return (bWuFan ? true : false);
}

//妙手回春 
bool CCardFan::IsMiaoShouHuiChun(BOOL bMiaoShouHuiChun)
{
	return (bMiaoShouHuiChun ? true : false);
}

//海底捞月
bool CCardFan::IsHaiDiLaoYue(BOOL bHaiDiLaoYue)
{
	return (bHaiDiLaoYue ? true : false);
}

//杠上开花
bool CCardFan::IsGangShangKaiHua(BOOL bGangShangKaiHua)
{
	return (bGangShangKaiHua ? true : false);
}

// 抢杠和 
bool CCardFan::IsQiangGangHe(BOOL bQiangGangHe)
{
	return (bQiangGangHe ? true : false);
}

//12番

//全不靠 
bool CCardFan::IsQuanBuKao(BOOL bQuanBuKao)
{
	return (bQuanBuKao ? true : false);
}

//组合龙 
bool CCardFan::IsZuHeLong(BOOL bZuHeLong)
{
	return (bZuHeLong ? true : false);
}

//大于五 
bool CCardFan::IsDaYuWu(BYTE bAllCard[MAX_COUNT])
{
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 >= 0) && (bAllCard[i] % 9 <= 4) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//小于五 
bool CCardFan::IsXiaoYuWu(BYTE bAllCard[MAX_COUNT])
{
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 >= 5) && (bAllCard[i] % 9 <= 8) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//三风刻
bool CCardFan::IsSanFengKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//声明变量
	BYTE bFengKeNum = 0;
	for (BYTE i =0; i<bKeZiNum; i++)
	{
		if ((bKeZi[i] >= 27) && (bKeZi[i] <= 30))
		{
			bFengKeNum++;
		}
	}

	return ((bFengKeNum == 3) ? true : false);
}

//16番

//清龙 
bool CCardFan::IsQingLong(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			for (BYTE n = 0; n < bShunZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if (((bShunZi[i] % 9 == bShunZi[j] % 9 - 3) && (bShunZi[i] % 9 == bShunZi[n] % 9 - 6)) &&
						((bShunZi[i] == bShunZi[j] - 3) && (bShunZi[i]== bShunZi[n] - 6) && (bShunZi[j] == bShunZi[n] - 3)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//三色双龙会 
bool CCardFan::IsSanSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang)
{
	//条件判断
	if (bShunZiNum < 4)
	{
		return false;
	}

	//声明变量
	BYTE bLongNum = 0;
	BYTE bLongColor[2] = {0,0};

	//循环检测
	for (BYTE i = 0; i < 2; i++)
	{
		if ((bShunZi[i *(i + 1)] == bShunZi[i *(i + 1) + 1] - 6) && (bShunZi[i *(i + 1)] % 9 == bShunZi[i *(i + 1) + 1] % 9 - 6))
		{
			bLongColor[bLongNum] = bShunZi[i *(i + 1)] / 9;
			bLongNum++;
		}
	}

	if ((bLongNum == 2) && (bLongColor[0] != bLongColor[1]))
	{
		if ((bJiang % 9 == 4) && ((bJiang / 9 != bLongColor[0]) && (bJiang / 9 != bLongColor[1])) && (bJiang < 27))
		{
			return true;
		}
	}

	return false;
}

//一色三步高
bool CCardFan::IsYiSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = 0; j < bShunZiNum; j++)
		{
			for (BYTE n = 0; n < bShunZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if ((((bShunZi[i] % 9 == bShunZi[j] % 9 - 1) && (bShunZi[i] % 9 == bShunZi[n] % 9 - 2)) &&
						((bShunZi[i] == bShunZi[j] - 1) && (bShunZi[i]== bShunZi[n] - 2) && (bShunZi[j] == bShunZi[n] - 1))) ||
						(((bShunZi[i] % 9 == bShunZi[j] % 9 - 2) && (bShunZi[i] % 9 == bShunZi[n] % 9 - 4)) &&
						((bShunZi[i] == bShunZi[j] - 2) && (bShunZi[i]== bShunZi[n] - 4) && (bShunZi[j] == bShunZi[n] - 2))))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//全带五 
bool CCardFan::IsQuanDaiWu(BYTE bGang[4], BYTE bGangNum,BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum,BYTE bJiang)
{
	//杠牌检测
	for (BYTE i = 0; i < bGangNum; i++)
	{
		if ((bGang[i] % 9 != 4) || (bJiang > 26))
		{
			return false;
		}
	}

	//顺子检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		if ((bShunZi[i] % 9 != 2) && (bShunZi[i] % 9 != 3) && (bShunZi[i] % 9 != 4))
		{
			return false;
		}
	}

	//刻子检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] % 9 != 4) ||(bKeZi[i] > 26))
		{
			return false;
		}
	}

	//将牌检测
	if ((bJiang % 9 != 4) || (bJiang > 26))
	{
		return false;
	}

	return true;
}

//三同刻
bool CCardFan::IsSanTongKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//条件判断
	if (bKeZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		for (BYTE j = i + 1; j < bKeZiNum; j++)
		{
			for (BYTE n = j + 1; n < bKeZiNum; n++)
			{
				if ((bKeZi[i] % 9 == bKeZi[j] % 9) && (bKeZi[j] % 9 == bKeZi[n] % 9) && (bKeZi[i] % 9 == bKeZi[n] % 9) && (bKeZi[i] < 27) && (bKeZi[j] < 27) && (bKeZi[n] < 27))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//三暗刻 
bool CCardFan::IsSanAnKe(BYTE bAnKeNum)
{
	return ((bAnKeNum == 3) ? true : false);
}

//24番

//七对
bool CCardFan::IsQiDui(BOOL bQiDui)
{
	return (bQiDui ? true : false);
}

//七星不靠 
bool CCardFan::IsQiXingBuKao(BOOL bQiXingBuKao)
{
	return (bQiXingBuKao ? true : false);
}

//全双刻
bool CCardFan::IsQuanShuangKe(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//条件判断
	if (bKeZiNum != 4)
	{
		return false;
	}

	//刻子检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if (((bKeZi[i] % 9) % 2 == 0) || (bKeZi[i] > 27))
		{
			return false;
		}
	}

	//将牌检测
	if (((bJiang % 9) % 2 == 0) || (bJiang > 27))
	{
		return false;
	}

	return true;
}

//清一色 
bool CCardFan::IsQingYiSe(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bCardColor[4] = {0,0,0,0};
	BYTE bColorNum = 0;

	//颜色判断
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] >= 0) && (bAllCard[i] <= 8))
		{
			bCardColor[0] = 1;
		}
		if ((bAllCard[i] >= 9) && (bAllCard[i] <= 17))
		{
			bCardColor[1] = 1;
		}
		if ((bAllCard[i] >= 18) && (bAllCard[i] <= 26))
		{
			bCardColor[2] = 1;
		}
		if ((bAllCard[i] >= 27) && (bAllCard[i] <= 33))
		{
			bCardColor[3] = 1;
		}
	}

	//颜色统计
	for (BYTE n = 0; n < 4; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return ((bColorNum == 1) ? true : false);
}

//一色三同顺 
bool CCardFan::IsYiSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		for (BYTE j = i + 1; j < bShunZiNum; j++)
		{
			for (BYTE n = j + 1; n < bShunZiNum; n++)
			{
				if ((bShunZi[i] == bShunZi[j]) && (bShunZi[i]== bShunZi[n]) && (bShunZi[j] == bShunZi[n]))	
				{
					return true;
				}
			}
		}
	}

	return false;
}

//一色三节高 
bool CCardFan::IsYiSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//条件判断
	if (bKeZiNum < 3)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		for (BYTE j = 0; j < bKeZiNum; j++)
		{
			for (BYTE n = 0; n < bKeZiNum; n++)
			{
				if ((i != j) && (i != n) && (j != n))
				{
					if (((bKeZi[i] % 9 == bKeZi[j] % 9 - 1) && (bKeZi[i] % 9 == bKeZi[n] % 9 - 2)) &&
						((bKeZi[i] == bKeZi[j] - 1) && (bKeZi[i] == bKeZi[n] - 2) && (bKeZi[j] == bKeZi[n] - 1)) &&
						((bKeZi[i] < 27) && (bKeZi[j] < 27) && (bKeZi[n] < 27)))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//全大 
bool CCardFan::IsQuanDa(BYTE bAllCard[MAX_COUNT])
{
	//循环检测
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 < 6) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//全中 
bool CCardFan::IsQuanZhong(BYTE bAllCard[MAX_COUNT])
{
	//循环检测
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 < 3) || (bAllCard[i] % 9 > 5) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//全小 
bool CCardFan::IsQuanXiao(BYTE bAllCard[MAX_COUNT])
{
	//循环检测
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 > 2) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//32番

//一色四步高 
bool CCardFan::IsYiSeSiBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 4)
	{
		return false;
	}

	//顺子检测
	if ((((bShunZi[0] % 9 == bShunZi[1] % 9 - 1) && (bShunZi[0] % 9 == bShunZi[2] % 9 - 2) && (bShunZi[0] % 9 == bShunZi[3] % 9 - 3)) &&
		((bShunZi[0] == bShunZi[1] - 1) && (bShunZi[0]== bShunZi[2] - 2) && (bShunZi[0] == bShunZi[3] - 3) && (bShunZi[1] == bShunZi[2] - 1) && (bShunZi[1] == bShunZi[3] - 2) && (bShunZi[2] == bShunZi[3] - 1))) ||
		(((bShunZi[0] % 9 == bShunZi[1] % 9 - 2) && (bShunZi[0] % 9 == bShunZi[2] % 9 - 4) && (bShunZi[0] % 9 == bShunZi[3] % 9 - 6)) &&
		((bShunZi[0] == bShunZi[1] - 2) && (bShunZi[0]== bShunZi[2] - 4) && (bShunZi[0] == bShunZi[3] - 6) && (bShunZi[1] == bShunZi[2] - 2) && (bShunZi[1] == bShunZi[3] - 4) && (bShunZi[2] == bShunZi[3] - 2))))
	{
		return true;
	}

	return false;
}

//三杠 
bool CCardFan::IsSanGang(BYTE bGangNum)
{
	return ((bGangNum == 3) ? true : false);
}

//混幺九
bool CCardFan::IsHunYaoJiu(BYTE bAllCard[MAX_COUNT])
{
	for (BYTE i = 0; i< 14; i++)
	{
		if (((bAllCard[i] % 9 != 0) && (bAllCard[i] % 9 != 8)) && (bAllCard[i] < 27))
		{
			return false;
		}
	}

	return true;
}

//48番

//一色四同顺
bool CCardFan::IsYiSeSiTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//条件判断
	if (bShunZiNum < 4)
	{
		return false;
	}

	//顺子检测
	if ((bShunZi[0] == bShunZi[1]) && (bShunZi[0] == bShunZi[2]) && (bShunZi[0] == bShunZi[3]) && 
		(bShunZi[1] == bShunZi[2]) && (bShunZi[1] == bShunZi[3]) &&
		(bShunZi[2] == bShunZi[3]))
	{
		return true;
	}

	return false;
}

//一色四节高 
bool CCardFan::IsYiSeSiJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//条件判断
	if (bKeZiNum < 4)
	{
		return false;
	}

	//循环检测
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		for (BYTE j = 0; j < bKeZiNum; j++)
		{
			for (BYTE n = 0; n < bKeZiNum; n++)
			{
				for (BYTE m = 0; m < bKeZiNum; m++ )
				{
					if ((i != j) && (i != n) && (i != m) && (j != n) && (j != m) && (n != m))
					{
						if (((bKeZi[i] % 9 == bKeZi[j] % 9 - 1) && (bKeZi[i] % 9 == bKeZi[n] % 9 - 2) && (bKeZi[i] % 9 == bKeZi[m] % 9 - 3)) &&
							((bKeZi[i] == bKeZi[j] - 1) && (bKeZi[i] == bKeZi[n] - 2) && (bKeZi[i] == bKeZi[m] - 3) && (bKeZi[j] == bKeZi[n] - 1) && (bKeZi[j] == bKeZi[m] - 2) && (bKeZi[n] == bKeZi[m] - 1)) &&
							((bKeZi[i] < 27) && (bKeZi[j] < 27) && (bKeZi[n] < 27) && (bKeZi[m] < 27)))
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

//64番

//清幺九 
bool CCardFan::IsQingYaoJiu(BYTE bAllCard[MAX_COUNT])
{
    for (BYTE i = 0; i< 14; i++)
	{
		if (((bAllCard[i] % 9 != 0) && (bAllCard[i] % 9 != 8)) || (bAllCard[i] > 27))
		{
			return false;
		}
	}

	return true;
}

//小四喜 
bool CCardFan::IsXiaoSiXi(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//条件判断
	if (bKeZiNum < 3)
	{
		return false;
	}

	//声明变量
	BYTE bFenKeNum = 0;

	//刻子判断
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] > 26) && (bKeZi[i] < 31))
		{
			bFenKeNum++;
		}
	}

	//将牌判断
	if ((bJiang > 26) && (bJiang < 31) && (bFenKeNum == 3))
	{
		return true;
	}

	return false;
}

//小三元 
bool CCardFan::IsXiaoSanYuan(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//条件判断
	if (bKeZiNum < 3)
	{
		return false;
	}

	//声明变量
	BYTE bJianKeNum = 0;

	//刻子判断
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] > 30) && (bKeZi[i] < 34))
		{
			bJianKeNum++;
		}
	}

	//将牌判断
	if ((bJiang > 30) && (bJiang < 34) && (bJianKeNum == 2))
	{
		return true;
	}

	return false;
}

//字一色 
bool CCardFan::IsZiYiSe(BYTE bAllCard[MAX_COUNT])
{
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if (bAllCard[i] < 27)
		{
			return false;
		}
	}

	return true;
}

//四暗刻
bool CCardFan::IsSiAnKe(BYTE bAnKeNun)
{
	if (bAnKeNun != 4)
	{
		return false;
	}

	return true;
}

//一色双龙会 
bool CCardFan::IsYiSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang)
{
	//条件判断
	if (bShunZiNum < 4)
	{
		return false;
	}

	//声明变量
	BYTE bLongNum = 0;
	BYTE bLongColor[2] = {0,0};

	//循环检测
	for (BYTE i = 0; i < 2; i++)
	{
		if ((bShunZi[i] == bShunZi[i + 2] - 6) && (bShunZi[i] % 9 == bShunZi[i + 2] % 9 - 6))
		{
			bLongColor[bLongNum] = bShunZi[i] / 9;
			bLongNum++;
		}
	}

	if ((bLongNum == 2) && (bLongColor[0] == bLongColor[1]))
	{
		if ((bJiang % 9 == 4) && ((bJiang / 9 == bLongColor[0]) && (bJiang < 27)))
		{
			return true;
		}
	}

	return false;
}

//88番

//大四喜 
bool CCardFan::IsDaSiXi(BYTE bKeZi[4], BYTE bKeZiNun)
{
	if (bKeZiNun < 4)
	{
		return false;
	}

	//声明变量
	BYTE bFenKeNum = 0;
	for (BYTE i = 0; i < bKeZiNun; i++)
	{
		if ((bKeZi[i] > 26) && (bKeZi[i] < 31))
		{
			bFenKeNum++;
		}
	}

	return ((bFenKeNum == 4) ? true : false);
}

//大三元 
bool CCardFan::IsDaSanYuan(BYTE bKeZi[4], BYTE bKeZiNun)
{
	if (bKeZiNun < 3)
	{
		return false;
	}

	//声明变量
	BYTE bJianKeNum = 0;
	for (BYTE i = 0; i < bKeZiNun; i++)
	{
		if ((bKeZi[i] > 30) && (bKeZi[i] < 34))
		{
			bJianKeNum++;
		}
	}

	return ((bJianKeNum == 3) ? true : false);
}

//绿一色 
bool CCardFan::IsLuYiSe(BYTE bAllCard[MAX_COUNT])
{
	//声明变量
	BYTE bLu[6] = {19,20,21,23,25,32};
	BYTE bLuNum = 0;

	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		for (BYTE j = 0; j < 6; j++)
		{
			if (bAllCard[i] == bLu[j])
			{
				bLuNum ++;
				break;
			}
		}
	}

	return ((bLuNum == 14) ? true : false);
}

//九宝莲灯 
bool CCardFan::IsJiuBaoLianDeng(BYTE bAllCard[MAX_COUNT], BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum)
{
	//条件判断
	if (!IsQingYiSe(bAllCard))
	{
		return false;
	}

	BYTE bNum = bChiNum + bMingKeZiNum + bGangNum;

	if (bNum != 0)
	{
		return false;
	}

	//声明变量
	BYTE bCardData[9];
	BYTE bCardNum = 0;
	ZeroMemory(bCardData,sizeof(bCardData));

	//扑克数目
	for (BYTE i = 0; i < MAX_COUNT; i++)
	{
		bCardData[bAllCard[i] % 9]++;
	}

	for (BYTE i = 0; i < 9; i++)
	{
		if ((i == 0) || (i == 8))
		{
			if (bCardData[i] > 2)
			{
				bCardData[i] = 1;
			}
		}
		else if ((i > 0) && (i < 8))
		{
			if (bCardData[i] > 1)
			{
				bCardData[i] = 1;
			}
		}
	}

	for (BYTE i = 0; i < 9; i++)
	{
		if (bCardData[i] == 1)
		{
			bCardNum ++;
		}
	}

	return (bCardNum == 9 ? true : false);
}

//四杠 
bool CCardFan::IsSiGang(BYTE bGangNum)
{
	if (bGangNum != 4)
	{
		return false;
	}

	return true;
}

//连七对
bool CCardFan::IsLianQiDui(BOOL bQiDui, BYTE bCardIndex[MAX_INDEX])
{
	//条件判断
	if (!bQiDui)
	{
		return false;
	}

	//声明变量
	BYTE bBegin = 27, bEnd = 27, bCardNum = 0;

	//循环检测
	for (BYTE i = 0; i < 27; i++)
	{
		if (bCardIndex[i] != 0)
		{
			if (bBegin == 27)
			{
				bBegin = i;
			}

			bEnd = i;
			bCardNum++;
		}
	}

	if (((bEnd - 6) == bBegin) && (bCardNum == 7))
	{
		return true;
	}

	return false;
}

//十三幺
bool CCardFan::IsShiSanYao(BOOL bShiSanYao)
{
	return (bShiSanYao ? true : false);
}

//和一张牌
bool CCardFan::IsHeYiZhang(BYTE bCardIndex[MAX_INDEX], BYTE bHeCard)
{
	//声明变量
	BYTE bTempCardIndex[MAX_INDEX];
	CopyMemory(bTempCardIndex,bCardIndex,sizeof(bTempCardIndex));

	if (bTempCardIndex[bHeCard] == 0) 
	{
		return false;
	}
	bTempCardIndex[bHeCard]--;

	//循环检测
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (i == bHeCard) 
		{
			continue;
		}
		if (bTempCardIndex[i] < 4) 
		{
			bTempCardIndex[i]++;
			if (m_GameLogic.IsHe(bTempCardIndex) != HCT_NULL)
			{
				return false;
			}
			bTempCardIndex[i]--;		
		}
	}

	return true;
}

CString CCardFan::FanTransform(BYTE bFan)
{
	CString strFan;
	switch (bFan)
	{
	case 1:
		{
			strFan = "一般高";
			break;
		}
	case 2:
		{
			strFan = "喜相逢";
			break;
		}
	case 3:
		{
			strFan = "连六";
			break;
		}
	case 4:
		{
			strFan = "缺一门";
			break;
		}
	case 5:
		{
			strFan = "老少副";
			break;
		}
	case 6:
		{
			strFan = "幺九刻";
			break;
		}
	case 7:
		{
			strFan = "无字";
			break;
		}
	case 8:
		{
			strFan = "明杠";
			break;
		}
	case 9:
		{
			strFan = "边张";
			break;
		}
	case 10:
		{
			strFan = "坎张";
			break;
		}
	case 11:
		{
			strFan = "单钓将";
			break;
		}
	case 12:
		{
			strFan = "自摸";
			break;
		}
	case 13:
		{
			strFan = "花牌";
			break;
		}
	case 14:
		{
			strFan = "箭刻";
			break;
		}
	case 15:
		{
			strFan = "圈风刻";
			break;
		}
	case 16:
		{
			strFan = "门风刻";
			break;
		}
	case 17:
		{
			strFan = "门前清";
			break;
		}
	case 18:
		{
			strFan = "平和";
			break;
		}
	case 19:
		{
			strFan = "断幺";
			break;
		}
	case 20:
		{
			strFan = "四归一";
			break;
		}
	case 21:
		{
			strFan = "暗杠";
			break;
		}
	case 22:
		{
			strFan = "双暗刻";
			break;
		}
	case 23:
		{
			strFan = "双同刻";
			break;
		}
	case 24:
		{
			strFan = "不求人";
			break;
		}
	case 25:
		{
			strFan = "全带幺";
			break;
		}
	case 26:
		{
			strFan = "双明杠";
			break;
		}
	case 27:
		{
			strFan = "和绝张";
			break;
		}
	case 28:
		{
			strFan = "碰碰和";
			break;
		}
	case 29:
		{
			strFan = "混一色";
			break;
		}
	case 30:
		{
			strFan = "三色三步高";
			break;
		}
	case 31:
		{
			strFan = "五门齐";
			break;
		}
	case 32:
		{
			strFan = "全求人";
			break;
		}
	case 33:
		{
			strFan = "双箭刻";
			break;
		}
	case 34:
		{
			strFan = "双暗杠";
			break;
		}
	case 35:
		{
			strFan = "花龙";
			break;
		}
	case 36:
		{
			strFan = "三色三同顺";
			break;
		}
	case 37:
		{
			strFan = "推不倒";
			break;
		}
	case 38:
		{
			strFan = "三色三节高";
			break;
		}
	case 39:
		{
			strFan = "抢杠和";
			break;
		}
	case 40:
		{
			strFan = "杠上开花";
			break;
		}
	case 41:
		{
			strFan = "海底捞月";
			break;
		}
	case 42:
		{
			strFan = "妙手回春";
			break;
		}
	case 43:
		{
			strFan = "无番和";
			break;
		}
	case 44:
		{
			strFan = "全不靠";
			break;
		}
	case 45:
		{
			strFan = "组合龙";
			break;
		}
	case 46:
		{
			strFan = "三风刻";
			break;
		}
	case 47:
		{
			strFan = "小于五";
			break;
		}
	case 48:
		{
			strFan = "大于五";
			break;
		}
	case 49:
		{
			strFan = "清龙";
			break;
		}
	case 50:
		{
			strFan = "一色三步高";
			break;
		}
	case 51:
		{
			strFan = "全带五";
			break;
		}
	case 52:
		{
			strFan = "三色双龙会";
			break;
		}
	case 53:
		{
			strFan = "三暗刻";
			break;
		}
	case 54:
		{
			strFan = "三同刻";
			break;
		}
	case 55:
		{
			strFan = "清一色";
			break;
		}
	case 56:
		{
			strFan = "七对";
			break;
		}
	case 57:
		{
			strFan = "七星不靠";
			break;
		}
	case 58:
		{
			strFan = "全双刻";
			break;
		}
	case 59:
		{
			strFan = "一色三节高";
			break;
		}
	case 60:
		{
			strFan = "一色三同顺";
			break;
		}
	case 61:
		{
			strFan = "全大";
			break;
		}
	case 62:
		{
			strFan = "全中";
			break;
		}
	case 63:
		{
			strFan = "全小";
			break;
		}
	case 64:
		{
			strFan = "混幺九";
			break;
		}
	case 65:
		{
			strFan = "一色四步高";
			break;
		}
	case 66:
		{
			strFan = "三杠";
			break;
		}
	case 67:
		{
			strFan = "一色四节高";
			break;
		}
	case 68:
		{
			strFan = "一色四同顺";
			break;
		}
	case 69:
		{
			strFan = "小三元";
			break;
		}
	case 70:
		{
			strFan = "小四喜";
			break;
		}
	case 71:
		{
			strFan = "字一色";
			break;
		}
	case 72:
		{
			strFan = "一色双龙会";
			break;
		}
	case 73:
		{
			strFan = "四暗刻";
			break;
		}
	case 74:
		{
			strFan = "清幺九";
			break;
		}
	case 75:
		{
			strFan = "大三元";
			break;
		}
	case 76:
		{
			strFan = "大四喜";
			break;
		}
	case 77:
		{
			strFan = "十三幺";
			break;
		}
	case 78:
		{
			strFan = "绿一色";
			break;
		}
	case 79:
		{
			strFan = "九莲宝灯";
			break;
		}
	case 80:
		{
			strFan = "四杠";
			break;
		}
	case 81:
		{
			strFan = "连七对";
			break;
		}
	}
	return strFan;
}

//番数转换
CString CCardFan::FanShuTransform(BYTE bFan)
{
	//声明变量
	CString strFanShu;

	switch (bFan)
	{
	case 1:
	case 2:	
	case 3:	
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		{
			strFanShu = "1";
			break;
		}
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		{
			strFanShu = "2";
			break;
		}
	case 24:
	case 25:
	case 26:
	case 27:
		{
			strFanShu = "4";
			break;
		}
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
		{
			strFanShu = "6";
			break;
		}
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
		{
			strFanShu = "8";
			break;
		}
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
		{
			strFanShu = "12";
			break;
		}
	case 49:
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
		{
			strFanShu = "16";
			break;
		}
	case 55:
	case 56:
	case 57:
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
		{
			strFanShu = "24";
			break;
		}
	case 67:
	case 68:
	case 69:
	case 70:
	case 71:
		{
			strFanShu = "48";
			break;
		}
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
		{
			strFanShu = "64";
			break;
		}
	case 78:
	case 79:
	case 80:
	case 81:
		{
			strFanShu = "88";
			break;
		}
	}
	return strFanShu;
}

//////////////////////////////////////////////////////////////////////////
