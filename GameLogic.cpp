#include "StdAfx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameLogic::CGameLogic()
{
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//分析组合
bool CGameLogic::AnalyseCom(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
    BYTE cbIndexData[9];
	BYTE cbIndexNum = 0;
	BYTE cbIndexKind = 0; 
	ZeroMemory(cbIndexData,sizeof(cbIndexData));
	
	//扑克数目
	for (BYTE i = 0; i < 27; i++)
	{
		if (cbCardIndex[i] != 0)
		{
			cbIndexNum += cbCardIndex[i];
			cbIndexKind++; 
		}
	}

	//数目判断
	if (((cbIndexKind != cbIndexNum) || (cbIndexNum < 7)))
	{
		return false;
	}

	//转换扑克
	for (BYTE i = 0; i < 9; i++)
	{
		cbIndexData[i] = MAX_INDEX;
	}

	for (BYTE i = 0; i <27; i++)
	{
		if (cbCardIndex[i] != 0)
		{
			cbIndexData[i % 9] = i;
		}
	}

	//特殊处理
	if ((cbIndexNum < 9) && (cbIndexNum > 6))
	{
		for (BYTE i = 0; i < 9; i++)
		{
			if (cbIndexData[i] == MAX_INDEX)
			{
				BYTE cbIndex = i % 3;
				for (BYTE j = 0; j < 3; j++)
				{
					if (cbIndexData[cbIndex + j * 3] != MAX_INDEX)
					{
						cbIndexData[i] = cbIndexData[cbIndex + j * 3];
						break;
					}
				}
			}
		}

	}

	//扑克比较
	for (BYTE i = 0; i < 7; i ++)
	{
		if ((cbIndexData[i] / 9 == cbIndexData[i + 1] / 9) || (cbIndexData[i] / 9 == cbIndexData[i + 2] / 9) ||
			(cbIndexData[i + 1] / 9 == cbIndexData[i + 2] / 9))
		{
			return false;
		}
	}

	return true;
}

	//分析组合
bool CGameLogic::AnalyseComEx(BYTE cbCardIndex[MAX_INDEX])
{
    //声明变量
	BYTE bZuHe[3][3];
	ZeroMemory(bZuHe,sizeof(bZuHe));

	//组合扑克
	for (BYTE i = 0; i < 27; i++)
	{
	   if ((i % 9 < 3) && ((cbCardIndex[i]) && (cbCardIndex[i + 3]) && (cbCardIndex[i + 6])))
	   {
          bZuHe[i / 9][i % 9] = 1;
	   }
	}

	//比较扑克
	for (BYTE j = 0; j < 3 ; j++)
	{
		for (BYTE n = 0; n < 3 ; n++)
		{
			for (BYTE m = 0; m < 3 ; m++)
			{
               if (((j != n) && (j != m) && (n != m)) && ((bZuHe[0][j] == 1) && (bZuHe[1][n] == 1) && (bZuHe[2][m] == 1)))
			   {
				   cbCardIndex[j]--;
				   cbCardIndex[j + 3]--;
				   cbCardIndex[j + 6]--;
				   cbCardIndex[n + 9]--;
				   cbCardIndex[n + 12]--;
				   cbCardIndex[n + 15]--;
				   cbCardIndex[m + 18]--;
				   cbCardIndex[m + 21]--;
				   cbCardIndex[m + 24]--;

				   return true;
			   }
			}
		}
	}

	return false;
}

//普通胡牌
bool CGameLogic::PuTongHe(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bKindCardnum[4] = {0,0,0,0};

	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		bKindCardnum[i / 9] += cbCardIndex[i];
	}

	for (BYTE i = 0; i < 4; i++)
	{
		if ((bKindCardnum[i] % 3 == 2) ||(bKindCardnum[i] % 3 == 0))
		{
			return (AnalyseHe(cbCardIndex) ? true : false);
		}
		else 
		{
			return false;
		}
	}

	return false;
}

//分析和牌
bool CGameLogic::AnalyseHe(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	static BYTE bJiang = 0; 
	BYTE sum = 0; 

	//扑克数目
	for(BYTE i = 0; i < MAX_INDEX; i++)
	{
		sum += cbCardIndex[i]; 
	}

	if(sum == 0) 
	{
		bJiang = 0; 
		return true;
	}

	//循环检测
	for(BYTE i = 0; !cbCardIndex[i] && i < MAX_INDEX; i++);   
	{
		//刻子
		if ( cbCardIndex[i] >= 3 )               
		{ 
			cbCardIndex[i] -= 3;                 
			if(AnalyseHe(cbCardIndex))
			{
				return true; 
			}
			cbCardIndex[i] += 3;                 
		} 

		//将牌
		if ( !bJiang && cbCardIndex[i] >= 2 )     
		{ 
			bJiang = 1;                   
			cbCardIndex[i] -= 2;                 
			if(AnalyseHe(cbCardIndex))
			{
				return true; 
			}
			cbCardIndex[i] += 2;                 
			bJiang = 0;                   
		}

		//顺子
		if ( i > 26 )  
		{
			return false;
		}

		if( i % 9 != 7 && i % 9 != 8  && cbCardIndex[i + 1] && cbCardIndex[i + 2] )       
		{ 
			cbCardIndex[i]--; 
			cbCardIndex[i+1]--; 
			cbCardIndex[i+2]--;                  
			if(AnalyseHe(cbCardIndex)) 
			{
				return true;
			}
			cbCardIndex[i]++; 
			cbCardIndex[i+1]++; 
			cbCardIndex[i+2]++;                  
		} 
	}

	return false;
}

//七对胡牌
bool CGameLogic::QiDuiHe(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bDuiZiNum = 0;

	//循环检测
	for (BYTE i = 0;i < 34; i++)
	{
		if (cbCardIndex[i] == 2)
		{
			bDuiZiNum++;
		}

		if (cbCardIndex[i] == 4)
		{
			bDuiZiNum += 2;
		}	
	}

	//条件判断
	if (bDuiZiNum == 7)
	{
		return true;
	}

	return false;
}

//十三幺
bool CGameLogic::ShiSanYaoHe(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bCardIndex = 0;
	
	//类型数目
	for (BYTE i = 0; i < MAX_INDEX; i++)
	{
		if ((cbCardIndex[i] != 0) && ((i % 9 == 0) || (i % 9 == 8) || (i > 26)))
		{
			bCardIndex++;
		}
	}
    
	return ((bCardIndex == 13) ? true : false);
}

//全不靠
bool CGameLogic::QuanBuKao(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bZiCardNum = 0;
	BYTE bZiCardKind = 0;
	for (BYTE i = 27; i < MAX_INDEX; i++)
	{
		if (cbCardIndex[i] != 0)
		{
			bZiCardNum += cbCardIndex[i];
			bZiCardKind++;
		}
	}

	if ((bZiCardNum == bZiCardKind) && ((bZiCardNum == 5) || (bZiCardNum == 6)))
	{
		if (AnalyseCom(cbCardIndex))
		{
			return true;
		}
	}

	return false;
}

//组合龙
bool CGameLogic::ZuHeLong(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE cbTempCardIndex[MAX_INDEX];
	BYTE bZiCardNum = 0;
	CopyMemory(cbTempCardIndex,cbCardIndex,sizeof(cbTempCardIndex));

	if (AnalyseComEx(cbTempCardIndex))
	{
		if (PuTongHe(cbTempCardIndex))
		{
			return true;
		}
	}

	return false;
}

//七星不靠
bool CGameLogic::QiXingBuKao(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE bZiCardNum = 0;
	BYTE bZiCardKind = 0;
	for (BYTE i = 27; i < MAX_INDEX; i++)
	{
		if (cbCardIndex[i] != 0)
		{
			bZiCardNum += cbCardIndex[i];
			bZiCardKind++;
		}
	}

	if ((bZiCardNum == bZiCardKind) && (bZiCardNum == 7))
	{
		if (AnalyseCom(cbCardIndex))
		{
			return true;
		}
	}

	return false;
}


//胡牌信息
BYTE CGameLogic::IsHe(BYTE cbCardIndex[MAX_INDEX])
{
	//声明变量
	BYTE cbTempCardIndex[MAX_INDEX];
	CopyMemory(cbTempCardIndex,cbCardIndex,sizeof(cbTempCardIndex));

	//七对和牌
	if (QiDuiHe(cbTempCardIndex))
	{
		return HCT_QDHU;
	}
	//普通和牌
	else if (PuTongHe(cbTempCardIndex)) 
	{
		return HCT_PTHU;
	}
	//全不靠
	else if (QuanBuKao(cbTempCardIndex))
	{
		return HCT_QBKHU;
	}
	//组合龙
	else if (ZuHeLong(cbTempCardIndex))
	{
		return HCT_ZHLHU;
	}
	//七星不靠
	else if (QiXingBuKao(cbTempCardIndex))
	{
		return HCT_QXBKHU;
	}
	//十三幺
	else if (ShiSanYaoHe(cbTempCardIndex))
	{
		return HCT_SSYHU;
	}

	return HCT_NULL;
}

//有效判断
bool CGameLogic::IsValidCard(BYTE cbCardData)
{
	BYTE cbValue=(cbCardData&MASK_VALUE);
	BYTE cbColor=(cbCardData&MASK_COLOR)>>4;
	return (((cbValue>=1)&&(cbValue<=9)&&(cbColor<=2))||((cbValue>=1)&&(cbValue<=7)&&(cbColor==3)));
}

//扑克转换
BYTE CGameLogic::SwitchToCardData(BYTE cbCardIndex)
{
	ASSERT(cbCardIndex<34);
	return ((cbCardIndex/9)<<4)|(cbCardIndex%9+1);
}

//扑克转换
BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData)
{
	ASSERT(IsValidCard(cbCardData));
	return ((cbCardData&MASK_COLOR)>>4)*9+(cbCardData&MASK_VALUE)-1;
}

//扑克转换
BYTE CGameLogic::SwitchToCardData(BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[], BYTE bMaxCount)
{
	//转换扑克
	BYTE bPosition=0;
	for (BYTE i=0;i<MAX_INDEX;i++)
	{
		if (cbCardIndex[i]!=0)
		{
			for (BYTE j=0;j<cbCardIndex[i];j++)
			{
				ASSERT(bPosition<bMaxCount);
				cbCardData[bPosition++]=SwitchToCardData(i);
			}
		}
	}

	return bPosition;
}

//扑克转换
BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData[], BYTE bCardCount, BYTE cbCardIndex[MAX_INDEX])
{
	//设置变量
	ZeroMemory(cbCardIndex,sizeof(BYTE)*MAX_INDEX);

	//转换扑克
	for (BYTE i=0;i<bCardCount;i++)
	{
		ASSERT(IsValidCard(cbCardData[i]));
		cbCardIndex[SwitchToCardIndex(cbCardData[i])]++;
	}

	return bCardCount;
}

//////////////////////////////////////////////////////////////////////////
