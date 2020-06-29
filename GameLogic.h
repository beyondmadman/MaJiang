#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////

//数值定义
#define MAX_INDEX					34									//最大索引
#define MAX_COUNT					14									//最大数目
#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码

//组合类型
#define ACK_NULL					0x00								//没有类型
#define ACK_ZHENG                   0X01                                //正常类型
#define ACK_CHI					    0x02								//吃牌类型
#define ACK_PENG					0x04								//碰牌类型
#define ACK_MGANG					0x08								//明牌类型
#define ACK_AGANG					0x10						        //暗杠类型
													 
//////////////////////////////////////////////////////////////////////////

//胡牌类型
#define HCT_NULL					0x0000								//非胡类型
#define HCT_PTHU					0x0001								//普通类型
#define HCT_QDHU                    0x0002                              //七对类型
#define HCT_SSYHU                   0x0004                              //十三幺
#define HCT_QXBKHU                  0x0008                              //七星不靠
#define HCT_ZHLHU                   0x0010                              //组合龙
#define HCT_QBKHU                   0x0020                              //全不靠

//////////////////////////////////////////////////////////////////////////

//组合子项
struct tagWeaveItem
{
	BYTE							cbWeaveKind;						//组合类型
	BYTE							cbCardIndex;						//扑克系数
};

//和牌子项
struct tagHeItem
{
	BYTE                            cbHeType;                           //和牌类型
	BYTE                            cbMenFeng;                          //门风扑克
	BYTE                            cbQuanFeng;                         //圈风扑克
	BOOL                            bZiMo;                              //自摸
	BOOL                            bMiaoShouHuiChun;                   //妙手回春
	BOOL                            bHaiDiLaoYue;                       //海底捞月
	BOOL                            bGangShangKaiHua;                   //杠上开花
	BOOL                            bQiangGangHe;                       //抢杠和
	BOOL                            bHeJueZhang;                        //和绝张
	BYTE                            bHeCard;                            //和牌扑克
	BYTE                            bHua;                               //花牌
};

//////////////////////////////////////////////////////////////////////////

//游戏逻辑类
class CGameLogic
{
	//函数定义
public:
	//构造函数
	CGameLogic();
	//析构函数
	virtual ~CGameLogic();

	//辅助函数
public:
	//分析组合
	bool AnalyseCom(BYTE cbCardIndex[MAX_INDEX]);
	//分析组合
	bool AnalyseComEx(BYTE cbCardIndex[MAX_INDEX]);
	//普通胡牌
	bool PuTongHe(BYTE cbCardIndex[MAX_INDEX]);
	//分析和牌
	bool AnalyseHe(BYTE cbCardIndex[MAX_INDEX]);
	//七对胡牌
	bool QiDuiHe(BYTE cbCardIndex[MAX_INDEX]);
	//十三幺
	bool ShiSanYaoHe(BYTE cbCardIndex[MAX_INDEX]);
	//全不靠
	bool QuanBuKao(BYTE cbCardIndex[MAX_INDEX]);
	//组合龙
	bool ZuHeLong(BYTE cbCardIndex[MAX_INDEX]);
	//七星不靠
	bool QiXingBuKao(BYTE cbCardIndex[MAX_INDEX]);

	//主动函数
public:
	//胡牌信息
	BYTE IsHe(BYTE cbCardIndex[MAX_INDEX]);
	
	//转换函数
public:
	//有效判断
	bool IsValidCard(BYTE cbCardData);
	//扑克转换
	BYTE SwitchToCardData(BYTE cbCardIndex);
	//扑克转换
	BYTE SwitchToCardIndex(BYTE cbCardData);
	//扑克转换
	BYTE SwitchToCardData(BYTE cbCardIndex[], BYTE cbCardData[MAX_INDEX], BYTE bMaxCount);
	//扑克转换
	BYTE SwitchToCardIndex(BYTE cbCardData[MAX_INDEX], BYTE bCardCount, BYTE cbCardIndex[]);
};

//////////////////////////////////////////////////////////////////////////

#endif