#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////

//��ֵ����
#define MAX_INDEX					34									//�������
#define MAX_COUNT					14									//�����Ŀ
#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//�������
#define ACK_NULL					0x00								//û������
#define ACK_ZHENG                   0X01                                //��������
#define ACK_CHI					    0x02								//��������
#define ACK_PENG					0x04								//��������
#define ACK_MGANG					0x08								//��������
#define ACK_AGANG					0x10						        //��������
													 
//////////////////////////////////////////////////////////////////////////

//��������
#define HCT_NULL					0x0000								//�Ǻ�����
#define HCT_PTHU					0x0001								//��ͨ����
#define HCT_QDHU                    0x0002                              //�߶�����
#define HCT_SSYHU                   0x0004                              //ʮ����
#define HCT_QXBKHU                  0x0008                              //���ǲ���
#define HCT_ZHLHU                   0x0010                              //�����
#define HCT_QBKHU                   0x0020                              //ȫ����

//////////////////////////////////////////////////////////////////////////

//�������
struct tagWeaveItem
{
	BYTE							cbWeaveKind;						//�������
	BYTE							cbCardIndex;						//�˿�ϵ��
};

//��������
struct tagHeItem
{
	BYTE                            cbHeType;                           //��������
	BYTE                            cbMenFeng;                          //�ŷ��˿�
	BYTE                            cbQuanFeng;                         //Ȧ���˿�
	BOOL                            bZiMo;                              //����
	BOOL                            bMiaoShouHuiChun;                   //���ֻش�
	BOOL                            bHaiDiLaoYue;                       //��������
	BOOL                            bGangShangKaiHua;                   //���Ͽ���
	BOOL                            bQiangGangHe;                       //���ܺ�
	BOOL                            bHeJueZhang;                        //�;���
	BYTE                            bHeCard;                            //�����˿�
	BYTE                            bHua;                               //����
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ�߼���
class CGameLogic
{
	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//��������
public:
	//�������
	bool AnalyseCom(BYTE cbCardIndex[MAX_INDEX]);
	//�������
	bool AnalyseComEx(BYTE cbCardIndex[MAX_INDEX]);
	//��ͨ����
	bool PuTongHe(BYTE cbCardIndex[MAX_INDEX]);
	//��������
	bool AnalyseHe(BYTE cbCardIndex[MAX_INDEX]);
	//�߶Ժ���
	bool QiDuiHe(BYTE cbCardIndex[MAX_INDEX]);
	//ʮ����
	bool ShiSanYaoHe(BYTE cbCardIndex[MAX_INDEX]);
	//ȫ����
	bool QuanBuKao(BYTE cbCardIndex[MAX_INDEX]);
	//�����
	bool ZuHeLong(BYTE cbCardIndex[MAX_INDEX]);
	//���ǲ���
	bool QiXingBuKao(BYTE cbCardIndex[MAX_INDEX]);

	//��������
public:
	//������Ϣ
	BYTE IsHe(BYTE cbCardIndex[MAX_INDEX]);
	
	//ת������
public:
	//��Ч�ж�
	bool IsValidCard(BYTE cbCardData);
	//�˿�ת��
	BYTE SwitchToCardData(BYTE cbCardIndex);
	//�˿�ת��
	BYTE SwitchToCardIndex(BYTE cbCardData);
	//�˿�ת��
	BYTE SwitchToCardData(BYTE cbCardIndex[], BYTE cbCardData[MAX_INDEX], BYTE bMaxCount);
	//�˿�ת��
	BYTE SwitchToCardIndex(BYTE cbCardData[MAX_INDEX], BYTE bCardCount, BYTE cbCardIndex[]);
};

//////////////////////////////////////////////////////////////////////////

#endif