#include "StdAfx.h"
#include ".\cardfan.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CCardFan::CCardFan(void)
{
	//�˿˱���
	ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	ZeroMemory(m_bHandCardIndex,sizeof(m_bHandCardIndex));
	ZeroMemory(m_bAllCard,sizeof(m_bAllCard));
	m_bAllCardNum = 0;

	//˳�ӱ���
	ZeroMemory(m_bShunZi,sizeof(m_bShunZi));            
	m_bShunZiNum = 0;            
	m_bChiNum = 0;               

	//���ӱ���
	ZeroMemory(m_bKeZi,sizeof(m_bKeZi));             
	m_bKeZiNum = 0;              
	m_bMingKeNum = 0;            
	m_bAnKeNum = 0;              

	//���Ʊ���
	ZeroMemory(m_bGang,sizeof(m_bGang));              
	m_bGangNum = 0;              
	m_bMingGangNum = 0;          
	m_bAnGangNum = 0;            

	//���Ʊ���
	m_bJiang = 0;              
}

//��������
CCardFan::~CCardFan(void)
{
}

//����˿�
void CCardFan::SplitCard(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//���ñ���
	ResetGameVariable();

	//����˿�
	SplitCardShunKe(cbCardIndex,WeaveItem,bItemCount);

	//�����ж�
	if (!((IsYiSeSiTongShun(m_bShunZi,m_bShunZiNum)) || (IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))))
	{
		SplitCardKeShun(cbCardIndex,WeaveItem,bItemCount);
	}
}

//����˿�
void CCardFan::SplitCardShunKe(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//���ñ���
	ResetGameVariable();

	//�˿˱���
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

	//�������˿�
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

	//��������˿�

	//˳��
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

	//����
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

	//����
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

//����˿�
void CCardFan::SplitCardKeShun(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount)
{
	//���ñ���
	ResetGameVariable();

	//�˿˱���
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

	//�������˿�
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

	//��������˿�

	//����
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

	//˳��
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

	//����
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

//���ñ���
void CCardFan::ResetGameVariable()
{
	//�˿˱���
	ZeroMemory(m_bCardIndex,sizeof(m_bCardIndex));
	ZeroMemory(m_bHandCardIndex,sizeof(m_bHandCardIndex));
	ZeroMemory(m_bAllCard,sizeof(m_bAllCard));
	m_bAllCardNum = 0;

	//˳�ӱ���
	ZeroMemory(m_bShunZi,sizeof(m_bShunZi));            
	m_bShunZiNum = 0;            
	m_bChiNum = 0;               

	//���ӱ���
	ZeroMemory(m_bKeZi,sizeof(m_bKeZi));             
	m_bKeZiNum = 0;              
	m_bMingKeNum = 0;            
	m_bAnKeNum = 0;              

	//���Ʊ���
	ZeroMemory(m_bGang,sizeof(m_bGang));              
	m_bGangNum = 0;              
	m_bMingGangNum = 0;          
	m_bAnGangNum = 0;            

	//���Ʊ���
	m_bJiang = 0;       
}

//ͳ�Ʒ���
void CCardFan::StatisticsFan(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount, tagHeItem HeItem)
{
	//����˿�
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

	//��������
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

	//����
	for (BYTE i = 0; i < HeItem.bHua; i++)
	{
		m_lFanList.push_back(13);
	}

	//�޷���
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


//��ͨ����
void CCardFan::PuTongFan()
{
	//���Ʒ���
	GangFan();
	//���ӷ���
	KeZiFan();
	//˳�ӷ���
	ShunZiFan();
	//��������
	QiTaFan();
}

//���ӷ���
void CCardFan::KeZiFan()
{
	if (m_bKeZiNum == 4)      //�Ŀ���
	{
		KeZiFan_1Part();
	}
	else if (m_bKeZiNum == 3) //������
	{
		KeZiFan_2Part();
	}
	else if (m_bKeZiNum == 2) //˫����
	{
		KeZiFan_3Part();
	}

	if (IsJiuBaoLianDeng(m_bAllCard,m_bChiNum,m_bMingKeNum,m_bGangNum))
	{
		m_bYaoJiuKe = false;
	}

	KeZiFan_4Part();
}

//���ӷ���
void CCardFan::KeZiFan_1Part()
{
	//����ϲ
	if (IsDaSiXi(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(76);
		m_bMenQuanFeng = false;
		m_bYaoJiuKe = false;
		m_bPengPengHe = false;

		//�İ���
		if (IsSiAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(73);
			m_bBuMen = false;
			m_bDanDiaoJiang = false;

			//��һɫ
			if (IsZiYiSe(m_bAllCard))
			{
				m_lFanList.push_back(71);
				m_bQingYiSe = false;
			}
			//���۾�
			else if (IsHunYaoJiu(m_bAllCard))
			{
				m_lFanList.push_back(64);
				m_bQuanDaiYao = false;
			}
		}
		//��һɫ
		else if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bQingYiSe = false;
		}
		//���۾�
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bQuanDaiYao = false;
		}
	}
	//���۾�
	else if (IsQingYaoJiu(m_bAllCard))
	{
		m_lFanList.push_back(74);
		m_bYaoJiuKe = false;
		m_bQuanDaiYao = false;
		m_bPengPengHe = false;

		//�İ���
		if (IsSiAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(73);
			m_bBuMen = false;
			m_bDanDiaoJiang = false;
		}
	}
	//�İ���
	else if (IsSiAnKe(m_bAnKeNum))
	{
		m_lFanList.push_back(73);
		m_bBuMen = false;
		m_bPengPengHe = false;
		m_bDanDiaoJiang = false;

		//��һɫ
		if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bYaoJiuKe = false;
			m_bQingYiSe = false;
		}
		//һɫ�Ľڸ�
		else if (IsYiSeSiJieGao(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(67);
			m_bPengPengHe = false;
		}
		//���۾�
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bYaoJiuKe = false;
			m_bQuanDaiYao = false;
		}
		//ȫ˫��
		else if (IsQuanShuangKe(m_bKeZi,m_bKeZiNum,m_bJiang))
		{
			m_lFanList.push_back(58);
			m_bDuanYao = false;
			m_bWuZi = false;
			
		}
	}
	//��һɫ
	else if (IsZiYiSe(m_bAllCard))
	{
		m_lFanList.push_back(71);
		m_bYaoJiuKe = false;
		m_bQingYiSe = false;
		m_bPengPengHe = false;
	}
	//һɫ�Ľڸ�
	else if (IsYiSeSiJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(67);
		m_bPengPengHe = false;
	}
	//���۾�
	else if (IsHunYaoJiu(m_bAllCard))
	{
		m_lFanList.push_back(64);
		m_bYaoJiuKe = false;
		m_bQuanDaiYao = false;
	}
	//ȫ˫��
	else if (IsQuanShuangKe(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(58);
		m_bPengPengHe = false;
		m_bDuanYao = false;
		m_bWuZi = false;
		
	}

	KeZiFan_2Part();
}

//���ӷ���
void CCardFan::KeZiFan_2Part()
{
	//����Ԫ
	if (IsDaSanYuan(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(75);
		m_bJianKe = false;
		m_bYaoJiuKe = false;
		
		//������
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//С��ϲ
	else if (IsXiaoSiXi(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(70);

		//������
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//һɫ���ڸ�
	else if (IsYiSeSanJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(59);

		//������
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//��ͬ��
	else if (IsSanTongKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(54);
		m_bShuangTongKe = false;

		//������
		if (IsSanAnKe(m_bAnKeNum))
		{
			m_lFanList.push_back(53);
		}
	}
	//������
	else if (IsSanAnKe(m_bAnKeNum))
	{
		m_lFanList.push_back(53);

		//�����
		if (IsSanFengKe(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(46);
		}
	}
	//�����
	else if (IsSanFengKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(46);
	}
	//��ɫ���ڸ�
	else if (IsSanSeSanJieGao(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(38);
	}

	KeZiFan_3Part();
}

//���ӷ���
void CCardFan::KeZiFan_3Part()
{
	//С��Ԫ
	if (IsXiaoSanYuan(m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(69);
		m_bJianKe = false;
		m_bYaoJiuKe = false;
	}
	//˫����
	else if (IsShuangJianKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(33);
		m_bYaoJiuKe = false;

		//˫����
		if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
		{
			m_lFanList.push_back(22);
		}
	}
	//˫ͬ��
	else if (IsShuangTongKe(m_bKeZi,m_bKeZiNum) && m_bShuangTongKe)
	{
		m_lFanList.push_back(23);

		//˫����
		if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
		{
			m_lFanList.push_back(22);
		}
	}
	//˫����
	else if (IsShuangAnKe(m_bAnKeNum) && m_bShuangAnKe)
	{
		m_lFanList.push_back(22);
	}
}

//���ӷ���
void CCardFan::KeZiFan_4Part()
{
	//��������
	BYTE bYaoJiuKe = IsYaoJiuKe(m_bKeZi,m_bKeZiNum);
	BYTE bSanFenKe = IsSanFengKe(m_bKeZi,m_bKeZiNum);

	//�ŷ��
	if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)) && m_bMenQuanFeng)
	{
		m_lFanList.push_back(16);

		//Ȧ���
		if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)) && m_bMenQuanFeng)
		{
			m_lFanList.push_back(15);

			//����
			if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
			{
				m_lFanList.push_back(14);

				//�۾ſ�
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
			//�۾ſ�
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
		//����
		else if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
		{
			m_lFanList.push_back(14);

			//�۾ſ�
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
					::AfxMessageBox("�۾ſ�");
					m_lFanList.push_back(6);
				}
			}
		}
		//�۾ſ�
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
	//Ȧ���
	else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)) && (m_bMenQuanFeng))
	{
		m_lFanList.push_back(15);

		//����
		if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
		{
			::AfxMessageBox("����");
			m_lFanList.push_back(14);

			//�۾ſ�
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
		//�۾ſ�
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
	//����
	else if (IsJianKe(m_bKeZi,m_bKeZiNum) && m_bJianKe)
	{
		m_lFanList.push_back(14);

		//�۾ſ�
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
	//�۾ſ�
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

//˳�ӷ���
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

//˳�ӷ���
void CCardFan::ShunZiFan_1Part()
{
	//һɫ˫����
	if (IsYiSeShuangLongHui(m_bShunZi,m_bShunZiNum,m_bJiang))
	{
		m_lFanList.push_back(72);
		m_bQingYiSe = false;
		m_bPingHe = false;
		m_bWuZi = false;
	}
	//һɫ��ͬ˳
	else if (IsYiSeSiTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(68);
		m_bSiGuiYi = false;
	}
	//һɫ�Ĳ���
	else if (IsYiSeSiBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(65);

		//���ٸ�
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);
		}
		//����
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
	}
	//һɫ��ͬ˳
	else if (IsYiSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(60);

		ShunZiFan_3Part();
	}
	//��ɫ˫����
	else if (IsSanSeShuangLongHui(m_bShunZi,m_bShunZiNum,m_bJiang))
	{
		m_lFanList.push_back(52);
		m_bPingHe = false;
		m_bWuZi = false;
	}
	//һɫ������
	else if (IsYiSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(50);

		ShunZiFan_3Part();
	}
	//����
	else if (IsQingLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(49);

		//ϲ���
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//��ɫ��ͬ˳
	else if (IsSanSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(36);

		//���ٸ�
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);
		}
		//����
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//����
	else if (IsHuaLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(35);

		//���ٸ�
		if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(5);

			//����
			if (IsLianLiu(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(3);
			}
			//ϲ���
			else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//һ���
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//����
		else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);

			//ϲ���
			if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//һ���
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//ϲ���
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//һ���
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//��ɫ������
	else if (IsSanSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(30);

		ShunZiFan_3Part();
	}
	//���ٸ�
	else if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);

		//����
		if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);

			//ϲ���
			if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(2);
			}
			//һ���
			else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//ϲ���
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//һ���
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//����
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);

		//ϲ���
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);

			//һ���
			if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
			{
				m_lFanList.push_back(1);
			}
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//ϲ���
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);

		//һ���
		if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//һ���
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//˳�ӷ���
void CCardFan::ShunZiFan_2Part()
{
	//һɫ��ͬ˳
	if (IsYiSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(60);
	}
	//һɫ������
	else if (IsYiSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(50);
	}
	//����
	else if (IsQingLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(49);
	}
	//��ɫ��ͬ˳
	else if (IsSanSeSanTongShun(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(36);
	}
	//����
	else if (IsHuaLong(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(35);
	}
	//��ɫ������
	else if (IsSanSeSanBuGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(30);
	}
	//���ٸ�
	else if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);

		//����
		if (IsLianLiu(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(3);
		}
		//ϲ���
		else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//����
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);

		//ϲ���
		if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(2);
		}
		//һ���
		else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//ϲ���
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);

		//һ���
		if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(1);
		}
	}
	//һ���
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//˳�ӷ���
void CCardFan::ShunZiFan_3Part()
{
	//���ٸ�
	if (IsLaoShaoFu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(5);
	}
	//����
	else if (IsLianLiu(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(3);
	}
	//ϲ���
	else if (IsXiXiangFeng(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(2);
	}
	//һ���
	else if (IsYiBanGao(m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(1);
	}
}

//���Ʒ���
void CCardFan::GangFan()
{
	if (m_bGangNum == 4)      //�ĸ���
	{
		//�ĸ�
		if (IsSiGang(m_bGangNum))
		{
			m_lFanList.push_back(80);
			m_bDanDiaoJiang = false;
			m_bPengPengHe = false;
		}
	}
	else if (m_bGangNum == 3) //������
	{
		//����
		if (IsSanGang(m_bGangNum))
		{
			m_lFanList.push_back(66);
		}
	}
	else if (m_bGangNum == 2) //������
	{
		//˫����
		if (IsShuangAnGang(m_bAnGangNum))
		{
			m_lFanList.push_back(34);
			m_bShuangAnKe = false;
		}
		//˫����
		if (IsShuangMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(26);
		}
	}
	else if (m_bGangNum == 1) //һ����
	{

		if (IsAnGang(m_bAnGangNum)) 
		{
			m_lFanList.push_back(21);
		}
		//����
		else if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
}

//��������
void CCardFan::QiTaFan()
{
	QiTaFan_1Part();
	QiTaFan_2Part();
	QiTaFan_3Part();
	QiTaFan_4Part();
	QiTaFan_5Part();
}

//��������
void CCardFan::QiTaFan_1Part()
{
	//�ű�����
	if (IsJiuBaoLianDeng(m_bAllCard,m_bChiNum,m_bMingKeNum,m_bGangNum))
	{
		m_lFanList.push_back(79);
		m_bBuMen = false;
		m_bWuZi = false;
	}
	//��һɫ
	else if (IsLuYiSe(m_bAllCard))
	{
		m_lFanList.push_back(78);

		//��һɫ
		if (IsQingYiSe(m_bAllCard) && m_bQingYiSe)
		{
			m_lFanList.push_back(55);
			m_bWuZi = false;
		}
	}
	//ȫС
	else if (IsQuanXiao(m_bAllCard))
	{
		m_lFanList.push_back(63);
		m_bWuZi = false;
	}
	//ȫ��
	else if (IsQuanZhong(m_bAllCard))
	{
		m_lFanList.push_back(62);
		m_bDuanYao = false;

		//ȫ����
		if(IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))
		{
			m_lFanList.push_back(51);
		}
	}
	//ȫ��
	else if (IsQuanDa(m_bAllCard))
	{
		m_lFanList.push_back(61);
		m_bWuZi = false;
	}
	//��һɫ
	else if(IsQingYiSe(m_bAllCard) && m_bQingYiSe)
	{
		m_lFanList.push_back(55);
		m_bWuZi = false;

		//������
		if (IsDaYuWu(m_bAllCard))
		{
			m_lFanList.push_back(48);

			//������
			if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
			{
				m_lFanList.push_back(28);
			}
		}
		//С����
		else if (IsXiaoYuWu(m_bAllCard))
		{
			m_lFanList.push_back(47);

			//������
			if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
			{
				m_lFanList.push_back(28);
			}
		}
		//������
		else if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
		{
			m_lFanList.push_back(28);
		}
	}
	//ȫ����
	else if(IsQuanDaiWu(m_bGang,m_bGangNum,m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bJiang))
	{
		m_lFanList.push_back(51);
		m_bDuanYao = false;
	}
	//������
	else if (IsDaYuWu(m_bAllCard))
	{
		m_lFanList.push_back(48);
		m_bWuZi = false;
	}
	//С����
	else if (IsXiaoYuWu(m_bAllCard))
	{
		m_lFanList.push_back(47);
		m_bWuZi = false;
	}
	//��һɫ
	else if (IsHunYiSe(m_bAllCard))
	{
		m_lFanList.push_back(29);
		
		//������
		if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
		{
			m_lFanList.push_back(28);
		}
	}
	//������
	else if (IsPengPengHe(m_bKeZiNum,m_bGangNum) && m_bPengPengHe)
	{
		m_lFanList.push_back(28);
	}
}

//��������
void CCardFan::QiTaFan_2Part()
{
	//���ֻش�
	if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
	{
		m_lFanList.push_back(42);
		m_bZiMo = false; 

		//���Ͽ���
		if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
		{
			m_lFanList.push_back(40);
		}
	}
	//��������
	else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
	{
		m_lFanList.push_back(41);

		//���ܺ�
		if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
	}
	//���Ͽ���
	else if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
	{
		m_lFanList.push_back(40);
		m_bZiMo = false;
	}
	//���ܺ�
	else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
	{
		m_lFanList.push_back(39);
        m_bHeJueZhang = false;
	}
}

//��������
void CCardFan::QiTaFan_3Part()
{
	//��������
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);
	
	//�Ʋ���
	if (IsTuiBuDao(m_bAllCard))
	{
		m_lFanList.push_back(37);

		//ȫ����
		if (IsQuanQiuRen(m_HeItem.bZiMo,bHeYiZhang,m_HeItem.bHeCard,m_bJiang,m_bChiNum,m_bMingKeNum,m_bMingGangNum))
		{
			m_lFanList.push_back(32);
			m_bDanDiaoJiang = false;
		}
		//������
		else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
			{
				m_lFanList.push_back(27);
			}
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
		{
			m_lFanList.push_back(27);

			//��ǰ��
			if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(17);
			}
			//����
			else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
			{
				m_lFanList.push_back(12);
			}
		}
		//��ǰ��
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);
		}
	}
	//ȫ����
	else if (IsQuanQiuRen(m_HeItem.bZiMo,bHeYiZhang,m_HeItem.bHeCard,m_bJiang,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(32);
		m_bDanDiaoJiang = false;

		//������
		if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
		//ȱһ��
		else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//������
	else if (IsWuMenQi(m_bAllCard))
	{
		m_lFanList.push_back(31);

		//������
		if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
			{
				m_lFanList.push_back(27);
			}
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
		{
			m_lFanList.push_back(27);

			//��ǰ��
			if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(17);
			}
			//����
			else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
			{
				m_lFanList.push_back(12);
			}
		}
		//��ǰ��
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);
		}
	}
	//�;���
	else if (IsHeJueZhang(m_HeItem.bHeJueZhang) && m_bHeJueZhang)
	{
		m_lFanList.push_back(27);

		//������
		if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);

			//ȱһ��
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//��ǰ��
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(17);

			//ȱһ��
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
		{
			m_lFanList.push_back(12);

			//ȱһ��
			if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
			{
				m_lFanList.push_back(4);
			}
		}
		//ȱһ��
		else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//������
	else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(24);

		//ȱһ��
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//��ǰ��
	else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bBuMen)
	{
		m_lFanList.push_back(17);

		//ȱһ��
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//����
	else if (IsZiMo(m_HeItem.bZiMo) && m_bZiMo)
	{
		m_lFanList.push_back(12);

		//ȱһ��
		if (IsQueYiMen(m_bAllCard) && m_bQueYiMen)
		{
			m_lFanList.push_back(4);
		}
	}
	//ȱһ��
	else if (IsQueYiMen(m_bAllCard) && m_bQueYiMen) 
	{
		m_lFanList.push_back(4);
	}
}

//��������
void CCardFan::QiTaFan_4Part()
{
	//��������
	BYTE bSiGuiYi = IsSiGuiYi(m_bHandCardIndex);

	//ȫ����
	if (IsQuanDaiYao(m_bShunZi,m_bShunZiNum,m_bKeZi,m_bKeZiNum,m_bGang,m_bGangNum,m_bJiang) && m_bQuanDaiYao)
	{
		m_lFanList.push_back(25);

		//�Ĺ�һ
		if (bSiGuiYi && m_bSiGuiYi)
		{
			for (BYTE i = 0; i < bSiGuiYi; i++)
			{
				m_lFanList.push_back(20);
			}
		}
	}
	//�Ĺ�һ
	else if (bSiGuiYi && m_bSiGuiYi)
	{
		for (BYTE i = 0; i < bSiGuiYi; i++)
		{
			m_lFanList.push_back(20);
		}

		//����
		if ((IsDuanYao(m_bAllCard)) && (m_bDuanYao))
		{
			m_lFanList.push_back(19);
		}
		//����
		else if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//����
	else if ((IsDuanYao(m_bAllCard)) && (m_bDuanYao))
	{
		m_lFanList.push_back(19);
	}
	//����
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);
	}
}

//��������
void CCardFan::QiTaFan_5Part()
{
	//��������
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);
	
	//ƽ��
	if (IsPingHe(m_bShunZiNum,m_bJiang) && m_bPingHe)
	{
		m_lFanList.push_back(18);

		//������
		if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang) && m_bDanDiaoJiang)
		{
			m_lFanList.push_back(11);
		}
		//����
		else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(10);
		}
		//����
		else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
		{
			m_lFanList.push_back(9);
		}
	}
	//������
	else if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang) && m_bDanDiaoJiang)
	{
		m_lFanList.push_back(11);
	}
	//����
	else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(10);
	}
	//����
	else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(9);
	}
}

//�߶Է���
void CCardFan::QiDuiFan()
{
	QiDuiFan_1Part();
	QiDuiFan_2Part();
	QiDuiFan_3Part();
}

//�߶Է���
void CCardFan::QiDuiFan_1Part()
{
	//��������
	BOOL bQiDui = true;
	
	//���߶�
	if (IsLianQiDui(bQiDui,m_bCardIndex))
	{
		m_lFanList.push_back(81);
		m_bWuZi = false;
	}
	//�߶�
	else if (IsQiDui(bQiDui))
	{
		m_lFanList.push_back(56);

		//��һɫ
		if (IsLuYiSe(m_bAllCard))
		{
			m_lFanList.push_back(78);

			//��һɫ
			if (IsQingYiSe(m_bAllCard))
			{
				m_lFanList.push_back(55);
				m_bWuZi = false;
			}
		}
		//���۾�
		else if (IsQingYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(74);
			m_bWuZi = false;
		}
		//��һɫ
		else if (IsZiYiSe(m_bAllCard))
		{
			m_lFanList.push_back(71);
			m_bWuZi = false;
		}
		//���۾�
		else if (IsHunYaoJiu(m_bAllCard))
		{
			m_lFanList.push_back(64);
			m_bWuZi = false;
		}
		//��һɫ
		else if (IsQingYiSe(m_bAllCard) && m_bQingYiSe)
		{
			m_lFanList.push_back(55);
			m_bWuZi = false;

			//������
			if (IsDaYuWu(m_bAllCard))
			{
				m_lFanList.push_back(48);
				m_bWuZi = false;
			}
			//С����
			else if (IsXiaoYuWu(m_bAllCard))
			{
				m_lFanList.push_back(47);
				m_bWuZi = false;
			}
		}
		//ȫС
		else if (IsQuanXiao(m_bAllCard))
		{
			m_lFanList.push_back(63);
			m_bWuZi = false;
		}
		//ȫ��
		else if (IsQuanZhong(m_bAllCard))
		{
			m_lFanList.push_back(62);
			m_bDuanYao = false;
		}
		//ȫ��
		else if (IsQuanDa(m_bAllCard))
		{
			m_lFanList.push_back(61);
			m_bWuZi = false;
		}
		//������
		else if (IsDaYuWu(m_bAllCard))
		{
			m_lFanList.push_back(48);
			m_bWuZi = false;
		}
		//С����
		else if (IsXiaoYuWu(m_bAllCard))
		{
			m_lFanList.push_back(47);
			m_bWuZi = false;
		}
		//��һɫ
		else if (IsHunYiSe(m_bAllCard))
		{
			m_lFanList.push_back(29);
		}		
	}
}

//�߶Է���
void CCardFan::QiDuiFan_2Part()
{
	//���ֻش�
	if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
	{
		m_lFanList.push_back(42);

		//�Ʋ���
		if (IsTuiBuDao(m_bAllCard))
		{
			m_lFanList.push_back(37);
		}
		//������
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
	}
	//��������
	else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
	{
		m_lFanList.push_back(41);

		//�Ʋ���
		if (IsTuiBuDao(m_bAllCard))
		{
			m_lFanList.push_back(37);
		}
		//������
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);
		}
	}
	//�Ʋ���
	if (IsTuiBuDao(m_bAllCard))
	{
		m_lFanList.push_back(37);

		//����
		if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
	//������
	else if (IsWuMenQi(m_bAllCard))
	{
		m_lFanList.push_back(31);

		//����
		if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
	//����
	else if (IsZiMo(m_HeItem.bZiMo))
	{
		m_lFanList.push_back(12);
	}
}

//�߶Է���
void CCardFan::QiDuiFan_3Part()
{
	//��������
	BYTE bSiGuiYi = IsSiGuiYi(m_bHandCardIndex);
	
	//�Ĺ�һ
	if (bSiGuiYi)
	{
		for (BYTE i = 0; i < bSiGuiYi; i++)
		{
			m_lFanList.push_back(20);
		}

		//����
		if ((IsDuanYao(m_bAllCard)))
		{
			m_lFanList.push_back(19);

			//ȱһ��
			if (IsQueYiMen(m_bAllCard))
			{
				m_lFanList.push_back(4);
			}
		}
		//����
		else if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);

			//ȱһ��
			if (IsQueYiMen(m_bAllCard))
			{
				m_lFanList.push_back(4);
			}
		}
		//ȱһ��
		else if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//����
	else if ((IsDuanYao(m_bAllCard)))
	{
		m_lFanList.push_back(19);

		//ȱһ��
		if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//����
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);

		//ȱһ��
		if (IsQueYiMen(m_bAllCard))
		{
			m_lFanList.push_back(4);
		}
	}
	//ȱһ��
	else if (IsQueYiMen(m_bAllCard))
	{
		m_lFanList.push_back(4);
	}
}

//ʮ����
void CCardFan::ShiSanYaoFan()
{
	//��������
	BOOL bShiSanYao = true;
	
	//ʮ����
	if (IsShiSanYao(bShiSanYao))
	{
		::AfxMessageBox("ʮ����");

		//���ֻش�
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			::AfxMessageBox("���ֻش�");

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				::AfxMessageBox("�;���");
			}
		}
		//��������
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			::AfxMessageBox("��������");

			//���ܺ�
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				::AfxMessageBox("���ܺ�");
			}
		}
		//���ܺ�
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			::AfxMessageBox("���ܺ�");
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			::AfxMessageBox("�;���");

			//����
			if (IsZiMo(m_HeItem.bZiMo))
			{
				::AfxMessageBox("����");
			}
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			::AfxMessageBox("����");
		}
	}
}

//���ǲ�������
void CCardFan::QiXingBuKaoFan()
{
	//��������
	BOOL bQiXingBuKao = true;
	
	//���ǲ���
	if (IsQiXingBuKao(bQiXingBuKao))
	{
		m_lFanList.push_back(57);

		//���ֻش�
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);
			}
		}
		//��������
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//���ܺ�
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);
			}
		}
		//���ܺ�
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//����
			if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//���������
void CCardFan::ZuHeLongFan()
{
	ZuHeLongFan_1Part();
	ZuHeLongFan_2Part();
	ZuHeLongFan_3Part();
}

//���������
void CCardFan::ZuHeLongFan_1Part()
{
	//��������
	BOOL bZuHeLong = true;
	
	//�����
	if (IsZuHeLong(bZuHeLong))
	{
		m_lFanList.push_back(45);
		
		//���ֻش�
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//���Ͽ���
			if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
			{
				m_lFanList.push_back(40);

				//������
				if (IsWuMenQi(m_bAllCard))
				{
					m_lFanList.push_back(31);

					//�;���
					if (IsHeJueZhang(m_HeItem.bHeJueZhang))
					{
						m_lFanList.push_back(27);

						//������
						if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
						{
							m_lFanList.push_back(24);
						}
					}
					//������
					else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//�;���
				else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//������
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//������
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//������
			else if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//�;���
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//������
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//������
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//�;���
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//������
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//������
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
		}
		//��������
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//���ܺ�
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);

				//������
				if (IsWuMenQi(m_bAllCard))
				{
					m_lFanList.push_back(31);

					//��ǰ��
					if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
					{
						m_lFanList.push_back(17);
					}
				}
				//��ǰ��
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//������
			else if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//�;���
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//��ǰ��
					if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
					{
						m_lFanList.push_back(17);
					}
				}
				//��ǰ��
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//�;���
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//��ǰ��
				if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//��ǰ��
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
		}
		//���Ͽ���
		else if (IsGangShangKaiHua(m_HeItem.bGangShangKaiHua))
		{
			m_lFanList.push_back(40);

			//������
			if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//�;���
				if (IsHeJueZhang(m_HeItem.bHeJueZhang))
				{
					m_lFanList.push_back(27);

					//������
					if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
					{
						m_lFanList.push_back(24);
					}
				}
				//������
				else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//�;���
			else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//������
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
			}
			//������
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
		}
		//���ܺ�
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);

			//������
			if (IsWuMenQi(m_bAllCard))
			{
				m_lFanList.push_back(31);

				//��ǰ��
				if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
			}
			//��ǰ��
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
		}
		//������
		else if (IsWuMenQi(m_bAllCard))
		{
			m_lFanList.push_back(31);

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);

				//������
				if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
				{
					m_lFanList.push_back(24);
				}
				//��ǰ��
				else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
				{
					m_lFanList.push_back(17);
				}
				//����
				else if (IsZiMo(m_HeItem.bZiMo))
				{
					m_lFanList.push_back(12);
				}
			}
			//������
			else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
			//��ǰ��
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
			//����
			else if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//������
			if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
			{
				m_lFanList.push_back(24);
			}
			//��ǰ��
			else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
			{
				m_lFanList.push_back(17);
			}
			//����
			else if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//������
		else if (IsBuQiuRen(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bMingGangNum) && m_bBuMen)
		{
			m_lFanList.push_back(24);
		}
		//��ǰ��
		else if (IsMenQianQing(m_HeItem.bZiMo,m_bChiNum,m_bMingKeNum,m_bGangNum) && m_bSiAnKe)
		{
			m_lFanList.push_back(17);
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//���������
void CCardFan::ZuHeLongFan_2Part()
{
	//����
	if (IsAnGang(m_bAnGangNum)) 
	{
		m_lFanList.push_back(21);
		
		//�ŷ��
		if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(16);
			
			//Ȧ���
			if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
			{
				m_lFanList.push_back(15);
			}
		}
		//Ȧ���
		else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(15);
		}
		//����
		else if (IsJianKe(m_bKeZi,m_bKeZiNum))
		{
			m_lFanList.push_back(14);
		}
		//�۾ſ�
		else if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
		{
			m_lFanList.push_back(6);
		}
	}
	//�ŷ��
	else if ((IsMenFengKe(m_HeItem.cbMenFeng,m_bKeZi,m_bKeZiNum)))
	{
		m_lFanList.push_back(16);

		//Ȧ���
		if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
		{
			m_lFanList.push_back(15);

			//����
			if (IsMingGang(m_bMingGangNum))
			{
				m_lFanList.push_back(8);
			}
		}
		//����
		else if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//Ȧ���
	else if ((IsQuanFengKe(m_HeItem.cbQuanFeng,m_bKeZi,m_bKeZiNum)))
	{
		m_lFanList.push_back(15);

		//����
		if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//����
	else if (IsJianKe(m_bKeZi,m_bKeZiNum))
	{
		m_lFanList.push_back(14);

		//����
		if (IsMingGang(m_bMingGangNum))
		{
			m_lFanList.push_back(8);
		}
	}
	//����
	else if (IsMingGang(m_bMingGangNum))
	{
		m_lFanList.push_back(8);

		//�۾ſ�
		if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
		{
			m_lFanList.push_back(6);
		}
	}
	//�۾ſ�
	else if (IsYaoJiuKe(m_bKeZi,m_bKeZiNum)) 
	{
		m_lFanList.push_back(6);
	}
}

//���������
void CCardFan::ZuHeLongFan_3Part()
{
	//��������
	BOOL bHeYiZhang = IsHeYiZhang(m_bHandCardIndex,m_HeItem.bHeCard);

	//������
	if (IsDanDiaoJiang(bHeYiZhang,m_HeItem.bHeCard,m_bJiang))
	{
		m_lFanList.push_back(11);

		//����
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//����
	else if (IsKanZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(10);

		//����
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//����
	else if (IsBianZhang(bHeYiZhang,m_HeItem.bHeCard, m_bShunZi,m_bShunZiNum))
	{
		m_lFanList.push_back(9);

		//����
		if (IsWuZi(m_bAllCard) && m_bWuZi)
		{
			m_lFanList.push_back(7);
		}
	}
	//����
	else if (IsWuZi(m_bAllCard) && m_bWuZi)
	{
		m_lFanList.push_back(7);
	}
}

//ȫ��������
void CCardFan::QuanBuKaoFan()
{
	//��������
	BOOL bQuanBuKao = true;
	
	//ȫ����
	if (IsQuanBuKao(bQuanBuKao))
	{
		m_lFanList.push_back(44);

		//���ֻش�
		if (IsMiaoShouHuiChun(m_HeItem.bMiaoShouHuiChun))
		{
			m_lFanList.push_back(42);

			//�;���
			if (IsHeJueZhang(m_HeItem.bHeJueZhang))
			{
				m_lFanList.push_back(27);
			}
		}
		//��������
		else if (IsHaiDiLaoYue(m_HeItem.bHaiDiLaoYue))
		{
			m_lFanList.push_back(41);

			//���ܺ�
			if (IsQiangGangHe(m_HeItem.bQiangGangHe))
			{
				m_lFanList.push_back(39);
			}
		}
		//���ܺ�
		else if (IsQiangGangHe(m_HeItem.bQiangGangHe))
		{
			m_lFanList.push_back(39);
		}
		//�;���
		else if (IsHeJueZhang(m_HeItem.bHeJueZhang))
		{
			m_lFanList.push_back(27);

			//����
			if (IsZiMo(m_HeItem.bZiMo))
			{
				m_lFanList.push_back(12);
			}
		}
		//����
		else if (IsZiMo(m_HeItem.bZiMo))
		{
			m_lFanList.push_back(12);
		}
	}
}

//1��

//һ���
bool CCardFan::IsYiBanGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 2)
	{
		return false;
	}

	//ѭ�����
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

//ϲ���
bool CCardFan::IsXiXiangFeng(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 2)
	{
		return false;
	}

	//ѭ�����
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

//����
bool CCardFan::IsLianLiu(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 2)
	{
		return false;
	}

	//ѭ�����
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

//���ٸ�
bool CCardFan::IsLaoShaoFu(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 2)
	{
		return false;
	}

	//ѭ�����
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

//�۾ſ�
BYTE CCardFan::IsYaoJiuKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//��������
	BYTE bYaoJiuNum = 0;

	//ѭ�����
	for (BYTE i =0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] % 9 == 0) || (bKeZi[i] % 9 == 8) || (bKeZi[i] > 26))
		{
			bYaoJiuNum++;
		}
	}

	return bYaoJiuNum;
}

//����
BYTE CCardFan::IsMingGang(BYTE bMingGanNum)
{
	return bMingGanNum;
}

//ȱһ��
bool CCardFan::IsQueYiMen(BYTE bAllCard[MAX_COUNT])
{
	//��������
	BYTE bCardColor[3] = {0,0,0};
	BYTE bColorNum = 0;

	//��ɫ�ж�
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

	//��ɫͳ��
	for (BYTE n = 0; n < 3; n++)
	{
		bColorNum += bCardColor[n];
	}

	return ((bColorNum == 2) ? true : false);
}

//����
bool CCardFan::IsWuZi(BYTE bAllCard[MAX_COUNT])
{
	//ѭ�����
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//����
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

//����
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

//������
bool CCardFan::IsDanDiaoJiang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bJiang)
{
	if (bHeYiZhang && (bHeCard == bJiang))
	{
		return true;
	}

	return false;
}

//����
bool CCardFan::IsZiMo(BOOL bZiMo)
{
	return (bZiMo ? true : false);
}

//����
BYTE CCardFan::IsHuaPai(BYTE bHuaNum)
{
	return bHuaNum;
}

//2��

//����
BOOL CCardFan::IsJianKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//��������
	BYTE bJanKeNum = 0;

	//ѭ�����
	for (BYTE i =0; i< bKeZiNum; i++)
	{
		if ((bKeZi[i] >= 31) && (bKeZi[i] <= 33))
		{
			bJanKeNum++;
		}
	}

	return ((bJanKeNum == 1) ? true : false);
}

//Ȧ���
bool CCardFan::IsQuanFengKe(BYTE bQuanFeng, BYTE bKeZi[4], BYTE bKeZiNum)
{
	//ѭ�����
	for (BYTE i =0; i < bKeZiNum; i++)
	{
		if (bKeZi[i] == bQuanFeng)
		{
			return true;
		}
	}

	return false;
}

//�ŷ��
bool CCardFan::IsMenFengKe(BYTE bMenFeng, BYTE bKeZi[4], BYTE bKeZiNum)
{
	//ѭ�����
	for (BYTE i =0; i< bKeZiNum; i++)
	{
		if (bKeZi[i] == bMenFeng)
		{
			return true;
		}
	}

	return false;
}

//��ǰ��
bool CCardFan::IsMenQianQing(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum)
{
	if (!bZiMo && (bMingKeZiNum == 0) && (bChiNum == 0)&& (bMingGangNum ==0))
	{
		return true;
	}

	return false;
}

//ƽ�� 
bool CCardFan::IsPingHe(BYTE bShunZiNum, BYTE bJiang)
{
	if ((bShunZiNum == 4) && (bJiang < 27))
	{
		return true;
	}

	return false;
}

//�Ĺ�һ
BYTE CCardFan::IsSiGuiYi(BYTE bCardIndex[MAX_INDEX])
{
	//��������
	BYTE bSiGuiYiNum = 0;

	//ѭ�����
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if (bCardIndex[i] == 4)
		{
			bSiGuiYiNum++;
		}
	}

	return bSiGuiYiNum ;
}

//˫ͬ��
bool CCardFan::IsShuangTongKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//�����ж�
	if (bKeZiNum > 1)
	{
		return false;
	}

	//ѭ�����
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

//˫����
bool CCardFan::IsShuangAnKe(BYTE bAnKeNum)
{
	return ((bAnKeNum == 2) ? true : false);
}

//���� 
BYTE CCardFan::IsAnGang(BYTE bAnGangNum)
{
	return bAnGangNum;
}

//���� 
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

//4��

//ȫ����
bool CCardFan::IsQuanDaiYao(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum, BYTE bGang[4], BYTE bGangNum, BYTE bJiang)
{
	//���˳��
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		if ((bShunZi[i] % 9 != 0) && (bShunZi[i] % 9 != 6)) 
		{
			return false;
		}
	}

	//������
	for (BYTE j = 0; j < bKeZiNum; j++)
	{
		if ((bKeZi[j] % 9 != 0) && (bKeZi[j] % 9 != 8)) 
		{
			return false;
		}
	}

	//������
	for (BYTE n = 0; n < bGangNum; n++)
	{
		if ((bGang[n] % 9 != 0) && (bGang[n] % 9 != 8)) 
		{
			return false;
		}
	}

	//��⽫��
	if (((bJiang % 9 != 0) && (bJiang % 9 != 8) && (bJiang < 27))) 
	{
		return false;
	}

	return true;
}

//������
bool CCardFan::IsBuQiuRen(BOOL bZiMo,BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum)
{
	if (bZiMo && (bMingKeZiNum == 0) && (bChiNum == 0) && (bMingGangNum == 0))
	{
		return true;
	}

	return false;
}

//˫����
bool CCardFan::IsShuangMingGang(BYTE bMingGangNum)
{
	return ((bMingGangNum == 2) ? true : false);
}

//�;���
bool CCardFan::IsHeJueZhang(BOOL bJueZhang)
{
	return (bJueZhang ? true : false);
}

//6 ��

//������
bool CCardFan::IsPengPengHe(BYTE bKeZiNum, BYTE bGangNum)
{
	//��������
	BYTE bPengPeng = bKeZiNum + bGangNum;
	
	if (bGangNum != 0)
	{
		bPengPeng -= bGangNum;
	}
	return ((bPengPeng == 4) ? true : false);
}

//��һɫ
bool CCardFan::IsHunYiSe(BYTE bAllCard[MAX_COUNT])
{
	//��������
	BYTE bCardColor[4] = {0,0,0,0};
	BYTE bColorNum = 0;

	//��ɫ�ж�
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

	//��ɫͳ��
	for (BYTE n = 0; n < 3; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return (((bColorNum == 1) && (bCardColor[3] == 1)) ? true : false);
}

//��ɫ������
bool CCardFan::IsSanSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//������
bool CCardFan::IsWuMenQi(BYTE bAllCard[MAX_COUNT])
{
	//��������
	BYTE bCardColor[5] = {0,0,0,0,0};
	BYTE bColorNum = 0;

	//��ɫ�ж�
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

	//��ɫͳ��
	for (BYTE n = 0; n < 5; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return ((bColorNum == 5) ? true : false);
}

//ȫ����
bool CCardFan::IsQuanQiuRen(BOOL bZiMo, BOOL bHeYiZhang, BYTE bHeCard, BYTE bJiang, BYTE bChiNum, BYTE bMingKeZiNum,BYTE bMingGangNum)
{
	//��������
	BYTE bCardNum = bChiNum + bMingKeZiNum + bMingGangNum;
	if (!bZiMo && (bHeYiZhang) && (bHeCard == bJiang) && (bCardNum == 4))
	{
		return true;
	}

	return false;
}

//˫����
bool CCardFan::IsShuangAnGang(BYTE bAnGangNum)
{
	return ((bAnGangNum == 2) ? true : false);
}

//˫����
bool CCardFan::IsShuangJianKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//��������
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

//8��

//����
bool CCardFan::IsHuaLong(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//�Ʋ��� 
bool CCardFan::IsTuiBuDao(BYTE bAllCard[MAX_COUNT])
{
	//��������
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

//��ɫ��ͬ˳
bool CCardFan::IsSanSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//��ɫ���ڸ�
bool CCardFan::IsSanSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//�����ж�
	if (bKeZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//�޷���
bool CCardFan::IsWuFanHe(BOOL bWuFan)
{
	return (bWuFan ? true : false);
}

//���ֻش� 
bool CCardFan::IsMiaoShouHuiChun(BOOL bMiaoShouHuiChun)
{
	return (bMiaoShouHuiChun ? true : false);
}

//��������
bool CCardFan::IsHaiDiLaoYue(BOOL bHaiDiLaoYue)
{
	return (bHaiDiLaoYue ? true : false);
}

//���Ͽ���
bool CCardFan::IsGangShangKaiHua(BOOL bGangShangKaiHua)
{
	return (bGangShangKaiHua ? true : false);
}

// ���ܺ� 
bool CCardFan::IsQiangGangHe(BOOL bQiangGangHe)
{
	return (bQiangGangHe ? true : false);
}

//12��

//ȫ���� 
bool CCardFan::IsQuanBuKao(BOOL bQuanBuKao)
{
	return (bQuanBuKao ? true : false);
}

//����� 
bool CCardFan::IsZuHeLong(BOOL bZuHeLong)
{
	return (bZuHeLong ? true : false);
}

//������ 
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

//С���� 
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

//�����
bool CCardFan::IsSanFengKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//��������
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

//16��

//���� 
bool CCardFan::IsQingLong(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//��ɫ˫���� 
bool CCardFan::IsSanSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang)
{
	//�����ж�
	if (bShunZiNum < 4)
	{
		return false;
	}

	//��������
	BYTE bLongNum = 0;
	BYTE bLongColor[2] = {0,0};

	//ѭ�����
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

//һɫ������
bool CCardFan::IsYiSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//ȫ���� 
bool CCardFan::IsQuanDaiWu(BYTE bGang[4], BYTE bGangNum,BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum,BYTE bJiang)
{
	//���Ƽ��
	for (BYTE i = 0; i < bGangNum; i++)
	{
		if ((bGang[i] % 9 != 4) || (bJiang > 26))
		{
			return false;
		}
	}

	//˳�Ӽ��
	for (BYTE i = 0; i < bShunZiNum; i++)
	{
		if ((bShunZi[i] % 9 != 2) && (bShunZi[i] % 9 != 3) && (bShunZi[i] % 9 != 4))
		{
			return false;
		}
	}

	//���Ӽ��
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] % 9 != 4) ||(bKeZi[i] > 26))
		{
			return false;
		}
	}

	//���Ƽ��
	if ((bJiang % 9 != 4) || (bJiang > 26))
	{
		return false;
	}

	return true;
}

//��ͬ��
bool CCardFan::IsSanTongKe(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//�����ж�
	if (bKeZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//������ 
bool CCardFan::IsSanAnKe(BYTE bAnKeNum)
{
	return ((bAnKeNum == 3) ? true : false);
}

//24��

//�߶�
bool CCardFan::IsQiDui(BOOL bQiDui)
{
	return (bQiDui ? true : false);
}

//���ǲ��� 
bool CCardFan::IsQiXingBuKao(BOOL bQiXingBuKao)
{
	return (bQiXingBuKao ? true : false);
}

//ȫ˫��
bool CCardFan::IsQuanShuangKe(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//�����ж�
	if (bKeZiNum != 4)
	{
		return false;
	}

	//���Ӽ��
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if (((bKeZi[i] % 9) % 2 == 0) || (bKeZi[i] > 27))
		{
			return false;
		}
	}

	//���Ƽ��
	if (((bJiang % 9) % 2 == 0) || (bJiang > 27))
	{
		return false;
	}

	return true;
}

//��һɫ 
bool CCardFan::IsQingYiSe(BYTE bAllCard[MAX_COUNT])
{
	//��������
	BYTE bCardColor[4] = {0,0,0,0};
	BYTE bColorNum = 0;

	//��ɫ�ж�
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

	//��ɫͳ��
	for (BYTE n = 0; n < 4; n++)
	{
		bColorNum +=bCardColor[n];
	}

	return ((bColorNum == 1) ? true : false);
}

//һɫ��ͬ˳ 
bool CCardFan::IsYiSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//һɫ���ڸ� 
bool CCardFan::IsYiSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//�����ж�
	if (bKeZiNum < 3)
	{
		return false;
	}

	//ѭ�����
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

//ȫ�� 
bool CCardFan::IsQuanDa(BYTE bAllCard[MAX_COUNT])
{
	//ѭ�����
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 < 6) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//ȫ�� 
bool CCardFan::IsQuanZhong(BYTE bAllCard[MAX_COUNT])
{
	//ѭ�����
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 < 3) || (bAllCard[i] % 9 > 5) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//ȫС 
bool CCardFan::IsQuanXiao(BYTE bAllCard[MAX_COUNT])
{
	//ѭ�����
	for (BYTE i = 0; i< MAX_COUNT; i++)
	{
		if ((bAllCard[i] % 9 > 2) || (bAllCard[i] > 26))
		{
			return false;
		}
	}

	return true;
}

//32��

//һɫ�Ĳ��� 
bool CCardFan::IsYiSeSiBuGao(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 4)
	{
		return false;
	}

	//˳�Ӽ��
	if ((((bShunZi[0] % 9 == bShunZi[1] % 9 - 1) && (bShunZi[0] % 9 == bShunZi[2] % 9 - 2) && (bShunZi[0] % 9 == bShunZi[3] % 9 - 3)) &&
		((bShunZi[0] == bShunZi[1] - 1) && (bShunZi[0]== bShunZi[2] - 2) && (bShunZi[0] == bShunZi[3] - 3) && (bShunZi[1] == bShunZi[2] - 1) && (bShunZi[1] == bShunZi[3] - 2) && (bShunZi[2] == bShunZi[3] - 1))) ||
		(((bShunZi[0] % 9 == bShunZi[1] % 9 - 2) && (bShunZi[0] % 9 == bShunZi[2] % 9 - 4) && (bShunZi[0] % 9 == bShunZi[3] % 9 - 6)) &&
		((bShunZi[0] == bShunZi[1] - 2) && (bShunZi[0]== bShunZi[2] - 4) && (bShunZi[0] == bShunZi[3] - 6) && (bShunZi[1] == bShunZi[2] - 2) && (bShunZi[1] == bShunZi[3] - 4) && (bShunZi[2] == bShunZi[3] - 2))))
	{
		return true;
	}

	return false;
}

//���� 
bool CCardFan::IsSanGang(BYTE bGangNum)
{
	return ((bGangNum == 3) ? true : false);
}

//���۾�
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

//48��

//һɫ��ͬ˳
bool CCardFan::IsYiSeSiTongShun(BYTE bShunZi[4], BYTE bShunZiNum)
{
	//�����ж�
	if (bShunZiNum < 4)
	{
		return false;
	}

	//˳�Ӽ��
	if ((bShunZi[0] == bShunZi[1]) && (bShunZi[0] == bShunZi[2]) && (bShunZi[0] == bShunZi[3]) && 
		(bShunZi[1] == bShunZi[2]) && (bShunZi[1] == bShunZi[3]) &&
		(bShunZi[2] == bShunZi[3]))
	{
		return true;
	}

	return false;
}

//һɫ�Ľڸ� 
bool CCardFan::IsYiSeSiJieGao(BYTE bKeZi[4], BYTE bKeZiNum)
{
	//�����ж�
	if (bKeZiNum < 4)
	{
		return false;
	}

	//ѭ�����
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

//64��

//���۾� 
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

//С��ϲ 
bool CCardFan::IsXiaoSiXi(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//�����ж�
	if (bKeZiNum < 3)
	{
		return false;
	}

	//��������
	BYTE bFenKeNum = 0;

	//�����ж�
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] > 26) && (bKeZi[i] < 31))
		{
			bFenKeNum++;
		}
	}

	//�����ж�
	if ((bJiang > 26) && (bJiang < 31) && (bFenKeNum == 3))
	{
		return true;
	}

	return false;
}

//С��Ԫ 
bool CCardFan::IsXiaoSanYuan(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang)
{
	//�����ж�
	if (bKeZiNum < 3)
	{
		return false;
	}

	//��������
	BYTE bJianKeNum = 0;

	//�����ж�
	for (BYTE i = 0; i < bKeZiNum; i++)
	{
		if ((bKeZi[i] > 30) && (bKeZi[i] < 34))
		{
			bJianKeNum++;
		}
	}

	//�����ж�
	if ((bJiang > 30) && (bJiang < 34) && (bJianKeNum == 2))
	{
		return true;
	}

	return false;
}

//��һɫ 
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

//�İ���
bool CCardFan::IsSiAnKe(BYTE bAnKeNun)
{
	if (bAnKeNun != 4)
	{
		return false;
	}

	return true;
}

//һɫ˫���� 
bool CCardFan::IsYiSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang)
{
	//�����ж�
	if (bShunZiNum < 4)
	{
		return false;
	}

	//��������
	BYTE bLongNum = 0;
	BYTE bLongColor[2] = {0,0};

	//ѭ�����
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

//88��

//����ϲ 
bool CCardFan::IsDaSiXi(BYTE bKeZi[4], BYTE bKeZiNun)
{
	if (bKeZiNun < 4)
	{
		return false;
	}

	//��������
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

//����Ԫ 
bool CCardFan::IsDaSanYuan(BYTE bKeZi[4], BYTE bKeZiNun)
{
	if (bKeZiNun < 3)
	{
		return false;
	}

	//��������
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

//��һɫ 
bool CCardFan::IsLuYiSe(BYTE bAllCard[MAX_COUNT])
{
	//��������
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

//�ű����� 
bool CCardFan::IsJiuBaoLianDeng(BYTE bAllCard[MAX_COUNT], BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum)
{
	//�����ж�
	if (!IsQingYiSe(bAllCard))
	{
		return false;
	}

	BYTE bNum = bChiNum + bMingKeZiNum + bGangNum;

	if (bNum != 0)
	{
		return false;
	}

	//��������
	BYTE bCardData[9];
	BYTE bCardNum = 0;
	ZeroMemory(bCardData,sizeof(bCardData));

	//�˿���Ŀ
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

//�ĸ� 
bool CCardFan::IsSiGang(BYTE bGangNum)
{
	if (bGangNum != 4)
	{
		return false;
	}

	return true;
}

//���߶�
bool CCardFan::IsLianQiDui(BOOL bQiDui, BYTE bCardIndex[MAX_INDEX])
{
	//�����ж�
	if (!bQiDui)
	{
		return false;
	}

	//��������
	BYTE bBegin = 27, bEnd = 27, bCardNum = 0;

	//ѭ�����
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

//ʮ����
bool CCardFan::IsShiSanYao(BOOL bShiSanYao)
{
	return (bShiSanYao ? true : false);
}

//��һ����
bool CCardFan::IsHeYiZhang(BYTE bCardIndex[MAX_INDEX], BYTE bHeCard)
{
	//��������
	BYTE bTempCardIndex[MAX_INDEX];
	CopyMemory(bTempCardIndex,bCardIndex,sizeof(bTempCardIndex));

	if (bTempCardIndex[bHeCard] == 0) 
	{
		return false;
	}
	bTempCardIndex[bHeCard]--;

	//ѭ�����
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
			strFan = "һ���";
			break;
		}
	case 2:
		{
			strFan = "ϲ���";
			break;
		}
	case 3:
		{
			strFan = "����";
			break;
		}
	case 4:
		{
			strFan = "ȱһ��";
			break;
		}
	case 5:
		{
			strFan = "���ٸ�";
			break;
		}
	case 6:
		{
			strFan = "�۾ſ�";
			break;
		}
	case 7:
		{
			strFan = "����";
			break;
		}
	case 8:
		{
			strFan = "����";
			break;
		}
	case 9:
		{
			strFan = "����";
			break;
		}
	case 10:
		{
			strFan = "����";
			break;
		}
	case 11:
		{
			strFan = "������";
			break;
		}
	case 12:
		{
			strFan = "����";
			break;
		}
	case 13:
		{
			strFan = "����";
			break;
		}
	case 14:
		{
			strFan = "����";
			break;
		}
	case 15:
		{
			strFan = "Ȧ���";
			break;
		}
	case 16:
		{
			strFan = "�ŷ��";
			break;
		}
	case 17:
		{
			strFan = "��ǰ��";
			break;
		}
	case 18:
		{
			strFan = "ƽ��";
			break;
		}
	case 19:
		{
			strFan = "����";
			break;
		}
	case 20:
		{
			strFan = "�Ĺ�һ";
			break;
		}
	case 21:
		{
			strFan = "����";
			break;
		}
	case 22:
		{
			strFan = "˫����";
			break;
		}
	case 23:
		{
			strFan = "˫ͬ��";
			break;
		}
	case 24:
		{
			strFan = "������";
			break;
		}
	case 25:
		{
			strFan = "ȫ����";
			break;
		}
	case 26:
		{
			strFan = "˫����";
			break;
		}
	case 27:
		{
			strFan = "�;���";
			break;
		}
	case 28:
		{
			strFan = "������";
			break;
		}
	case 29:
		{
			strFan = "��һɫ";
			break;
		}
	case 30:
		{
			strFan = "��ɫ������";
			break;
		}
	case 31:
		{
			strFan = "������";
			break;
		}
	case 32:
		{
			strFan = "ȫ����";
			break;
		}
	case 33:
		{
			strFan = "˫����";
			break;
		}
	case 34:
		{
			strFan = "˫����";
			break;
		}
	case 35:
		{
			strFan = "����";
			break;
		}
	case 36:
		{
			strFan = "��ɫ��ͬ˳";
			break;
		}
	case 37:
		{
			strFan = "�Ʋ���";
			break;
		}
	case 38:
		{
			strFan = "��ɫ���ڸ�";
			break;
		}
	case 39:
		{
			strFan = "���ܺ�";
			break;
		}
	case 40:
		{
			strFan = "���Ͽ���";
			break;
		}
	case 41:
		{
			strFan = "��������";
			break;
		}
	case 42:
		{
			strFan = "���ֻش�";
			break;
		}
	case 43:
		{
			strFan = "�޷���";
			break;
		}
	case 44:
		{
			strFan = "ȫ����";
			break;
		}
	case 45:
		{
			strFan = "�����";
			break;
		}
	case 46:
		{
			strFan = "�����";
			break;
		}
	case 47:
		{
			strFan = "С����";
			break;
		}
	case 48:
		{
			strFan = "������";
			break;
		}
	case 49:
		{
			strFan = "����";
			break;
		}
	case 50:
		{
			strFan = "һɫ������";
			break;
		}
	case 51:
		{
			strFan = "ȫ����";
			break;
		}
	case 52:
		{
			strFan = "��ɫ˫����";
			break;
		}
	case 53:
		{
			strFan = "������";
			break;
		}
	case 54:
		{
			strFan = "��ͬ��";
			break;
		}
	case 55:
		{
			strFan = "��һɫ";
			break;
		}
	case 56:
		{
			strFan = "�߶�";
			break;
		}
	case 57:
		{
			strFan = "���ǲ���";
			break;
		}
	case 58:
		{
			strFan = "ȫ˫��";
			break;
		}
	case 59:
		{
			strFan = "һɫ���ڸ�";
			break;
		}
	case 60:
		{
			strFan = "һɫ��ͬ˳";
			break;
		}
	case 61:
		{
			strFan = "ȫ��";
			break;
		}
	case 62:
		{
			strFan = "ȫ��";
			break;
		}
	case 63:
		{
			strFan = "ȫС";
			break;
		}
	case 64:
		{
			strFan = "���۾�";
			break;
		}
	case 65:
		{
			strFan = "һɫ�Ĳ���";
			break;
		}
	case 66:
		{
			strFan = "����";
			break;
		}
	case 67:
		{
			strFan = "һɫ�Ľڸ�";
			break;
		}
	case 68:
		{
			strFan = "һɫ��ͬ˳";
			break;
		}
	case 69:
		{
			strFan = "С��Ԫ";
			break;
		}
	case 70:
		{
			strFan = "С��ϲ";
			break;
		}
	case 71:
		{
			strFan = "��һɫ";
			break;
		}
	case 72:
		{
			strFan = "һɫ˫����";
			break;
		}
	case 73:
		{
			strFan = "�İ���";
			break;
		}
	case 74:
		{
			strFan = "���۾�";
			break;
		}
	case 75:
		{
			strFan = "����Ԫ";
			break;
		}
	case 76:
		{
			strFan = "����ϲ";
			break;
		}
	case 77:
		{
			strFan = "ʮ����";
			break;
		}
	case 78:
		{
			strFan = "��һɫ";
			break;
		}
	case 79:
		{
			strFan = "��������";
			break;
		}
	case 80:
		{
			strFan = "�ĸ�";
			break;
		}
	case 81:
		{
			strFan = "���߶�";
			break;
		}
	}
	return strFan;
}

//����ת��
CString CCardFan::FanShuTransform(BYTE bFan)
{
	//��������
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
