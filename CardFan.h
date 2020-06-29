#ifndef	CARD_FAN_HEAD_FILE
#define CARD_FAN_HEAD_FILE

#pragma once
#include "GameLogic.h"
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//�˿��㷬��
class CCardFan 
{
	//��������
public:
	//���캯��
	CCardFan(void);
	//��������
	virtual ~CCardFan(void);

	//��������
protected:
	//����˿�
    void SplitCard(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//����˿�
	void SplitCardShunKe(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//����˿�
	void SplitCardKeShun(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount);
	//���ñ���
	void ResetGameVariable();

public:
	//ͳ�Ʒ���
	void StatisticsFan(BYTE cbCardIndex[MAX_INDEX], tagWeaveItem WeaveItem[], BYTE bItemCount, tagHeItem HeItem);
	//��ͨ����
	void PuTongFan();
	//���ӷ���
	void KeZiFan();
	//���ӷ���
	void KeZiFan_1Part();
	//���ӷ���
	void KeZiFan_2Part();
	//���ӷ���
	void KeZiFan_3Part();
	//���ӷ���
	void KeZiFan_4Part();
	//˳�ӷ���
	void ShunZiFan();
	//˳�ӷ���
	void ShunZiFan_1Part();
	//˳�ӷ���
	void ShunZiFan_2Part();
	//˳�ӷ���
	void ShunZiFan_3Part();
	//���Ʒ���
	void GangFan();
	//��������
	void QiTaFan();
	//��������
	void QiTaFan_1Part();
	//��������
	void QiTaFan_2Part();
	//��������
	void QiTaFan_3Part();
	//��������
	void QiTaFan_4Part();
	//��������
	void QiTaFan_5Part();
	//�߶Է���
    void QiDuiFan();
	//�߶Է���
    void QiDuiFan_1Part();
	//�߶Է���
    void QiDuiFan_2Part();
	//�߶Է���
    void QiDuiFan_3Part();
	//ʮ���۷���
	void ShiSanYaoFan();
	//���ǲ�������
	void QiXingBuKaoFan();
	//���������
	void ZuHeLongFan();
	//���������
	void ZuHeLongFan_1Part();
	//���������
	void ZuHeLongFan_2Part();
	//���������
	void ZuHeLongFan_3Part();
	//ȫ��������
	void QuanBuKaoFan();
	
	//���ͺ���
protected:
	//1��
	//һ���
	bool IsYiBanGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//ϲ���
	bool IsXiXiangFeng(BYTE bShunZi[4], BYTE bShunZiNum);
	//����
	bool IsLianLiu(BYTE bShunZi[4], BYTE bShunZiNum);
	//���ٸ�
	bool IsLaoShaoFu(BYTE bShunZi[4], BYTE bShunZiNum);
	//�۾ſ�
	BYTE IsYaoJiuKe(BYTE bKeZi[4], BYTE bKeZiNun);
	//����
	BYTE IsMingGang(BYTE bMingGanNum);
	//ȱһ��
	bool IsQueYiMen(BYTE bAllCard[MAX_COUNT]);
	//����
	bool IsWuZi(BYTE bAllCard[MAX_COUNT]);
	//����
	bool IsBianZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunzi[4], BYTE bShunZiNum);
	//����
	bool IsKanZhang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bShunzi[4], BYTE bShunZiNum);
	//������
	bool IsDanDiaoJiang(BOOL bHeYiZhang ,BYTE bHeCard, BYTE bJiang);
	//����
	bool IsZiMo(BOOL bZiMo);
	//����
	BYTE IsHuaPai(BYTE bHuaNum);

	//2��
	//����
	BOOL IsJianKe(BYTE bKeZi[4], BYTE bKeZiNum); 
	//Ȧ���
	bool IsQuanFengKe(BYTE bQuanFeng, BYTE bKeZi[4], BYTE bKeZiNum);
	//�ŷ��
	bool IsMenFengKe(BYTE bMenFeng, BYTE bKeZi[4], BYTE bKeZiNum);
	//��ǰ��
	bool IsMenQianQing(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum);
	//ƽ�� 
	bool IsPingHe(BYTE bShunZiNum, BYTE bJiang);
	//�Ĺ�һ
	BYTE IsSiGuiYi(BYTE bCardIndex[MAX_INDEX]);
	//˫ͬ��
	bool IsShuangTongKe(BYTE bKeZi[4], BYTE bKeZiNum);
	//˫����
	bool IsShuangAnKe(BYTE bAnKeNum);
	//���� 
	BYTE IsAnGang(BYTE bAnGangNum);
	//���� 
	bool IsDuanYao(BYTE bAllCard[MAX_COUNT]);

	//4��
	//ȫ����
	bool IsQuanDaiYao(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum, BYTE bGang[4], BYTE bGangNum, BYTE bJiang);
	//������
	bool IsBuQiuRen(BOOL bZiMo, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum);
	//˫����
	bool IsShuangMingGang(BYTE bMingGangNum);
	//�;���
	bool IsHeJueZhang(BOOL bJueZhang);

	//6 ��
	//������
	bool IsPengPengHe(BYTE bKeZiNum, BYTE bGangNum);
	//��һɫ
	bool IsHunYiSe(BYTE bAllCard[MAX_COUNT]);
	//��ɫ������
	bool IsSanSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//������
	bool IsWuMenQi(BYTE bAllCard[MAX_COUNT]);
	//ȫ����
	bool IsQuanQiuRen(BOOL bZiMo, BOOL bHeYiZhang, BYTE bHeCard, BYTE bJiang, BYTE bChiNum, BYTE bMingKeZiNum, BYTE bMingGangNum);
	//˫����
	bool IsShuangAnGang(BYTE bAnGangNum);
	//˫����
	bool IsShuangJianKe(BYTE bKeZi[4], BYTE bKeZiNum);

	//8��
	//����
	bool IsHuaLong(BYTE bShunZi[4], BYTE bShunZiNum);
	//�Ʋ��� 
	bool IsTuiBuDao(BYTE bAllCard[MAX_COUNT]);
	//��ɫ��ͬ˳
	bool IsSanSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum);
	//��ɫ���ڸ�
	bool IsSanSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum);
	//�޷���
	bool IsWuFanHe(BOOL bWuFan);
	//���ֻش� 
	bool IsMiaoShouHuiChun(BOOL bMiaoShouHuiChun);
	//��������
	bool IsHaiDiLaoYue(BOOL bHaiDiLaoYue);
	//���Ͽ���
	bool IsGangShangKaiHua(BOOL bGangShangKaiHua);
	//���ܺ� 
	bool IsQiangGangHe(BOOL bQiangGangHe);

	//12��
	//ȫ���� 
	bool IsQuanBuKao(BOOL bQuanBuKao);
	//����� 
	bool IsZuHeLong(BOOL bZuHeLong);
	//������ 
	bool IsDaYuWu(BYTE bAllCard[MAX_COUNT]);
	//С���� 
	bool IsXiaoYuWu(BYTE bAllCard[MAX_COUNT]);
	//�����
	bool IsSanFengKe(BYTE bKeZi[4], BYTE bKeZiNum);

	//16��
	//���� 
	bool IsQingLong(BYTE bShunZi[4], BYTE bShunZiNum);
	//��ɫ˫���� 
	bool IsSanSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang);
	//һɫ������
	bool IsYiSeSanBuGao(BYTE bShunZi[4], BYTE bShunZiNum); 
	//ȫ���� 
	bool IsQuanDaiWu(BYTE bGang[4], BYTE bGangNum,BYTE bShunZi[4], BYTE bShunZiNum, BYTE bKeZi[4], BYTE bKeZiNum,BYTE bJiang);
	//��ͬ��
	bool IsSanTongKe(BYTE bKeZi[4], BYTE bKeZiNum);
	//������ 
	bool IsSanAnKe(BYTE bAnKeNun);

	//24��
	//�߶�
	bool IsQiDui(BOOL bQiDui);
	//���ǲ��� 
	bool IsQiXingBuKao(BOOL bQiXingBuKao);
	//ȫ˫��
	bool IsQuanShuangKe(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//��һɫ 
	bool IsQingYiSe(BYTE bAllCard[MAX_COUNT]);
	//һɫ��ͬ˳ 
	bool IsYiSeSanTongShun(BYTE bShunZi[4], BYTE bShunZiNum);
	//һɫ���ڸ� 
	bool IsYiSeSanJieGao(BYTE bKeZi[4], BYTE bKeZiNum);
	//ȫ�� 
	bool IsQuanDa(BYTE bAllCard[MAX_COUNT]);
	//ȫ�� 
	bool IsQuanZhong(BYTE bAllCard[MAX_COUNT]);
	//ȫС 
	bool IsQuanXiao(BYTE bAllCard[MAX_COUNT]);

	//32��
	//һɫ�Ĳ��� 
	bool IsYiSeSiBuGao(BYTE bShunZi[4], BYTE bShunZiNum);
	//���� 
	bool IsSanGang(BYTE bGangNum);
	//���۾�
	bool IsHunYaoJiu(BYTE bAllCard[MAX_COUNT]);

	//48��
	//14 һɫ��ͬ˳
	bool IsYiSeSiTongShun(BYTE bShunzi[4], BYTE bShunZiNum);
	//15 һɫ�Ľڸ� 
	bool IsYiSeSiJieGao(BYTE bKeZi[4], BYTE bKeZiNum);

	//64��
	//���۾� 
	bool IsQingYaoJiu(BYTE bAllCard[MAX_COUNT]);
	//С��ϲ 
	bool IsXiaoSiXi(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//С��Ԫ 
	bool IsXiaoSanYuan(BYTE bKeZi[4], BYTE bKeZiNum, BYTE bJiang);
	//��һɫ 
	bool IsZiYiSe(BYTE bAllCard[MAX_COUNT]);
	//�İ���
	bool IsSiAnKe(BYTE bAnKeNun);
	//һɫ˫���� 
	bool IsYiSeShuangLongHui(BYTE bShunZi[4], BYTE bShunZiNum, BYTE bJiang);

	//88��
	//����ϲ 
	bool IsDaSiXi(BYTE bKeZi[4], BYTE bKeZiNum);
	//����Ԫ 
	bool IsDaSanYuan(BYTE bKeZi[4], BYTE bKeZiNum);
	//��һɫ 
	bool IsLuYiSe(BYTE bAllCard[MAX_COUNT]);
	//�������� 
	bool IsJiuBaoLianDeng(BYTE bAllCard[MAX_COUNT],BYTE bChiNum, BYTE bMingKeZiNum, BYTE bGangNum);
	//�ĸ� 
	bool IsSiGang(BYTE bGangNum);
	//���߶�
	bool IsLianQiDui(BOOL bQiDui, BYTE bCardIndex[MAX_INDEX]);
	//ʮ����
	bool IsShiSanYao(BOOL bShiSanYao);

	//��������
protected:
	//��һ����
	bool IsHeYiZhang(BYTE bCardIndex[MAX_INDEX], BYTE bHeCard);

public:
	//����ת��
	CString FanTransform(BYTE bFan);
	//����ת��
	CString FanShuTransform(BYTE bFan);
 
    //�˿�����
protected:
	CGameLogic                    m_GameLogic;                        //��Ϸ�߼�
	
public:
	list<BYTE>                    m_lFanList;                         //���ͱ�

protected:
	BYTE                          m_bCardIndex[MAX_INDEX];            //�˿˱���
	BYTE                          m_bHandCardIndex[MAX_INDEX];        //�˿˱���
	BYTE                          m_bAllCard[14];                     //�˿˱���
	BYTE                          m_bAllCardNum;                      //�˿˱���

    BYTE                          m_bShunZi[4];                       //˳�ӱ���
	BYTE                          m_bShunZiNum;                       //˳�ӱ���
	BYTE                          m_bChiNum;                          //˳�ӱ���

	BYTE                          m_bKeZi[4];                         //���ӱ���
	BYTE                          m_bKeZiNum;                         //���ӱ���
	BYTE                          m_bMingKeNum;                       //���ӱ���
	BYTE                          m_bAnKeNum;                         //���ӱ���

	BYTE                          m_bGang[4];                         //���Ʊ���
	BYTE                          m_bGangNum;                         //���Ʊ���
	BYTE                          m_bMingGangNum;                     //���Ʊ���
	BYTE                          m_bAnGangNum;                       //���Ʊ���

	BYTE                          m_bJiang;                           //���Ʊ���

    tagHeItem                     m_HeItem;                           //��������

	BOOL                          m_bYaoJiuKe;                        //�۾ſ�
	BOOL                          m_bMenQuanFeng;                     //�ŷ�Ȧ��
	BOOL                          m_bBuMen;                           //����������
	BOOL                          m_bDuanYao;                         //����
	BOOL                          m_bSiGuiYi;                         //�Ĺ�һ
	BOOL                          m_bSiAnKe;                          //�İ���
	BOOL                          m_bQuanDaiYao;                      //ȫ����
	BOOL                          m_bPengPengHe;                      //������
	BOOL                          m_bQingYiSe;                        //��һɫ
	BOOL                          m_bPingHe;                          //ƽ��
	BOOL                          m_bWuZi;                            //����
	BOOL                          m_bDanDiaoJiang;                    //������
	BOOL                          m_bQueYiMen;                        //ȱһ��
	BOOL                          m_bShuangAnKe;                      //˫����
	BOOL                          m_bJianKe;                          //����
	BOOL                          m_bShuangTongKe;                    //˫ͬ��
	BOOL                          m_bZiMo;                            //����
	BOOL                          m_bHeJueZhang;                      //�;���
};

//////////////////////////////////////////////////////////////////////////

#endif
