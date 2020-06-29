#ifndef	CARD_FAN_HEAD_FILE
#define CARD_FAN_HEAD_FILE

#pragma once
#include "GameLogic.h"
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//扑克算番类
class CCardFan 
{
	//函数定义
public:
	//构造函数
	CCardFan(void);
	//析构函数
	virtual ~CCardFan(void);

	//分析函数
protected:
	//拆分扑克
    void SplitCard(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//拆分扑克
	void SplitCardShunKe(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//拆分扑克
	void SplitCardKeShun(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//重置变量
	void ResetGameVariable();

public:
	//统计番型
	void StatisticsFan(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount, tagHeItem HeItem);
	//普通番型
	void PuTongFan();
	//刻子番型
	void KeZiFan();
	//刻子番型
	void KeZiFan_1Part();
	//刻子番型
	void KeZiFan_2Part();
	//刻子番型
	void KeZiFan_3Part();
	//刻子番型
	void KeZiFan_4Part();
	//顺子番型
	void ShunZiFan();
	//顺子番型
	void ShunZiFan_1Part();
	//顺子番型
	void ShunZiFan_2Part();
	//顺子番型
	void ShunZiFan_3Part();
	//杠牌番型
	void GangFan();
	//其他番型
	void QiTaFan();
	//其他番型
	void QiTaFan_1Part();
	//其他番型
	void QiTaFan_2Part();
	//其他番型
	void QiTaFan_3Part();
	//其他番型
	void QiTaFan_4Part();
	//其他番型
	void QiTaFan_5Part();
	//七对翻型
    void QiDuiFan();
	//七对翻型
    void QiDuiFan_1Part();
	//七对翻型
    void QiDuiFan_2Part();
	//七对翻型
    void QiDuiFan_3Part();
	//十三幺番型
	void ShiSanYaoFan();
	//七星不靠番型
	void QiXingBuKaoFan();
	//组合龙番型
	void ZuHeLongFan();
	//组合龙番型
	void ZuHeLongFan_1Part();
	//组合龙番型
	void ZuHeLongFan_2Part();
	//组合龙番型
	void ZuHeLongFan_3Part();
	//全不靠番型
	void QuanBuKaoFan();
	
	//番型函数
protected:
	//1番
	//一般高
	bool IsYiBanGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//喜相逢
	bool IsXiXiangFeng(BYTE bShunZi[4], BYTE bShunZiNum);
	//连六
	bool IsLianLiu(BYTE bShunZi[4], BYTE bShunZiNum);
	//老少副
	bool IsLaoShaoFu(BYTE bShunZi[4], BYTE bShunZiNum);
	//幺九刻
	BYTE IsYaoJiuKe(BYTE bKeZi[4], BYTE bKeZiNun);
	//明杠
	BYTE IsMingGang(BYTE bMingGanNum);
	//缺一门
	bool IsQueYiMen(BYTE bAllCard[MAX_COUNT]);
	//无字
	bool IsWuZi(BYTE bAllCard[MAX_COUNT]);
	//边张
	bool IsBianZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunzi[4], BYTE bShunZiNum);
	//坎张
	bool IsKanZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunzi[4], BYTE bShunZiNum);
	//单钓将
	bool IsDanDiaoJiang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bJiang);
	//自摸
	bool IsZiMo(BOOL bZiMo);
	//花牌
	BYTE IsHuaPai(BYTE bHuaNum);

	//2番
	//箭刻
	BOOL IsJianKe(BYTE bKeZi[4], BYTE bKeZiNum); 
	//圈风刻
	bool IsQuanFengKe(BYTE bQuanFeng, BYTE bKeZi[4], BYTE bKeZiNum);
	//门风刻
	bool IsMenFengKe(BYTE bMenFeng, BYTE bKeZi[4], BYTE bKeZiNum);
	//门前清
	bool IsMenQianQing(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum);
	//平和 
	bool IsPingHe(BYTE bShunZiNum, BYTE bJiang);
	//四归一
	BYTE IsSiGuiYi(BYTE bCardIndex[MAX_INDEX]);
	//双同刻
	bool IsShuangTongKe(BYTE bKeZi[4], BYTE bKeZiNum);
	//双暗刻
	bool IsShuangAnKe(BYTE bAnKeNum);
	//暗杠 
	BYTE IsAnGang(BYTE bAnGangNum);
	//断幺 
	bool IsDuanYao(BYTE bAllCard[MAX_COUNT]);

	//4番
	//全带幺
	bool IsQuanDaiYao(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum, BYTE bGang[4], BYTE bGangNum, BYTE bJiang);
	//不求人
	bool IsBuQiuRen(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum);
	//双明杠
	bool IsShuangMingGang(BYTE bMingGangNum);
	//和绝张
	bool IsHeJueZhang(BOOL bJueZhang);

	//6 番
	//碰碰和
	bool IsPengPengHe(BYTE bKeZiNum, BYTE bGangNum);
	//混一色
	bool IsHunYiSe(BYTE bAllCard[MAX_COUNT]);
	//三色三步高
	bool IsSanSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//五门齐
	bool IsWuMenQi(BYTE bAllCard[MAX_COUNT]);
	//全求人
	bool IsQuanQiuRen(BOOL bZiMo, BOOL bHeYiZhang, BYTE bHeCard, BYTE bJiang, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum);
	//双暗杠
	bool IsShuangAnGang(BYTE bAnGangNum);
	//双箭刻
	bool IsShuangJianKe(BYTE bKeZi[4], BYTE bKeZiNum);

	//8番
	//花龙
	bool IsHuaLong(BYTE bShunZi[4], BYTE bShunZiNum);
	//推不倒 
	bool IsTuiBuDao(BYTE bAllCard[MAX_COUNT]);
	//三色三同顺
	bool IsSanSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum);
	//三色三节高
	bool IsSanSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum);
	//无番和
	bool IsWuFanHe(BOOL bWuFan);
	//妙手回春 
	bool IsMiaoShouHuiChun(BOOL bMiaoShouHuiChun);
	//海底捞月
	bool IsHaiDiLaoYue(BOOL bHaiDiLaoYue);
	//杠上开花
	bool IsGangShangKaiHua(BOOL bGangShangKaiHua);
	//抢杠和 
	bool IsQiangGangHe(BOOL bQiangGangHe);

	//12番
	//全不靠 
	bool IsQuanBuKao(BOOL bQuanBuKao);
	//组合龙 
	bool IsZuHeLong(BOOL bZuHeLong);
	//大于五 
	bool IsDaYuWu(BYTE bAllCard[MAX_COUNT]);
	//小于五 
	bool IsXiaoYuWu(BYTE bAllCard[MAX_COUNT]);
	//三风刻
	bool IsSanFengKe(BYTE bKeZi[4], BYTE bKeZiNum);

	//16番
	//清龙 
	bool IsQingLong(BYTE bShunZi[4], BYTE bShunZiNum);
	//三色双龙会 
	bool IsSanSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang);
	//一色三步高
	bool IsYiSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum); 
	//全带五 
	bool IsQuanDaiWu(BYTE bGang[4], BYTE bGangNum,BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum,BYTE bJiang);
	//三同刻
	bool IsSanTongKe(BYTE bKeZi[4], BYTE bKeZiNum);
	//三暗刻 
	bool IsSanAnKe(BYTE bAnKeNun);

	//24番
	//七对
	bool IsQiDui(BOOL bQiDui);
	//七星不靠 
	bool IsQiXingBuKao(BOOL bQiXingBuKao);
	//全双刻
	bool IsQuanShuangKe(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//清一色 
	bool IsQingYiSe(BYTE bAllCard[MAX_COUNT]);
	//一色三同顺 
	bool IsYiSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum);
	//一色三节高 
	bool IsYiSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum);
	//全大 
	bool IsQuanDa(BYTE bAllCard[MAX_COUNT]);
	//全中 
	bool IsQuanZhong(BYTE bAllCard[MAX_COUNT]);
	//全小 
	bool IsQuanXiao(BYTE bAllCard[MAX_COUNT]);

	//32番
	//一色四步高 
	bool IsYiSeSiBuGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//三杠 
	bool IsSanGang(BYTE bGangNum);
	//混幺九
	bool IsHunYaoJiu(BYTE bAllCard[MAX_COUNT]);

	//48番
	//14 一色四同顺
	bool IsYiSeSiTongShun(BYTE bShunzi[4], BYTE bShunZiNum);
	//15 一色四节高 
	bool IsYiSeSiJieGao(BYTE bKeZi[4], BYTE bKeZiNum);

	//64番
	//清幺九 
	bool IsQingYaoJiu(BYTE bAllCard[MAX_COUNT]);
	//小四喜 
	bool IsXiaoSiXi(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//小三元 
	bool IsXiaoSanYuan(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//字一色 
	bool IsZiYiSe(BYTE bAllCard[MAX_COUNT]);
	//四暗刻
	bool IsSiAnKe(BYTE bAnKeNun);
	//一色双龙会 
	bool IsYiSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang);

	//88番
	//大四喜 
	bool IsDaSiXi(BYTE bKeZi[4], BYTE bKeZiNum);
	//大三元 
	bool IsDaSanYuan(BYTE bKeZi[4], BYTE bKeZiNum);
	//绿一色 
	bool IsLuYiSe(BYTE bAllCard[MAX_COUNT]);
	//九莲宝灯 
	bool IsJiuBaoLianDeng(BYTE bAllCard[MAX_COUNT],BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum);
	//四杠 
	bool IsSiGang(BYTE bGangNum);
	//连七对
	bool IsLianQiDui(BOOL bQiDui, BYTE bCardIndex[MAX_INDEX]);
	//十三幺
	bool IsShiSanYao(BOOL bShiSanYao);

	//辅助函数
protected:
	//和一张牌
	bool IsHeYiZhang(BYTE bCardIndex[MAX_INDEX], BYTE bHeCard);

public:
	//番型转换
	CString FanTransform(BYTE bFan);
	//番数转换
	CString FanShuTransform(BYTE bFan);
 
    //扑克数据
protected:
	CGameLogic                    m_GameLogic;                        //游戏逻辑
	
public:
	list<BYTE>                    m_lFanList;                         //番型表

protected:
	BYTE                          m_bCardIndex[MAX_INDEX];            //扑克变量
	BYTE                          m_bHandCardIndex[MAX_INDEX];        //扑克变量
	BYTE                          m_bAllCard[14];                     //扑克变量
	BYTE                          m_bAllCardNum;                      //扑克变量

    BYTE                          m_bShunZi[4];                       //顺子变量
	BYTE                          m_bShunZiNum;                       //顺子变量
	BYTE                          m_bChiNum;                          //顺子变量

	BYTE                          m_bKeZi[4];                         //刻子变量
	BYTE                          m_bKeZiNum;                         //刻子变量
	BYTE                          m_bMingKeNum;                       //刻子变量
	BYTE                          m_bAnKeNum;                         //刻子变量

	BYTE                          m_bGang[4];                         //杠牌变量
	BYTE                          m_bGangNum;                         //杠牌变量
	BYTE                          m_bMingGangNum;                     //杠牌变量
	BYTE                          m_bAnGangNum;                       //杠牌变量

	BYTE                          m_bJiang;                           //将牌变量

    tagHeItem                     m_HeItem;                           //和牌子项

	BOOL                          m_bYaoJiuKe;                        //幺九刻
	BOOL                          m_bMenQuanFeng;                     //门风圈风
	BOOL                          m_bBuMen;                           //不求人门清
	BOOL                          m_bDuanYao;                         //断幺
	BOOL                          m_bSiGuiYi;                         //四归一
	BOOL                          m_bSiAnKe;                          //四暗刻
	BOOL                          m_bQuanDaiYao;                      //全带幺
	BOOL                          m_bPengPengHe;                      //碰碰和
	BOOL                          m_bQingYiSe;                        //清一色
	BOOL                          m_bPingHe;                          //平和
	BOOL                          m_bWuZi;                            //无字
	BOOL                          m_bDanDiaoJiang;                    //单钓将
	BOOL                          m_bQueYiMen;                        //缺一门
	BOOL                          m_bShuangAnKe;                      //双暗刻
	BOOL                          m_bJianKe;                          //箭刻
	BOOL                          m_bShuangTongKe;                    //双同刻
	BOOL                          m_bZiMo;                            //自摸
	BOOL                          m_bHeJueZhang;                      //和绝张
};

//////////////////////////////////////////////////////////////////////////

#endif
