//---------------------------------------------------------------------------

#ifndef uIMRIncl_allH
#define uIMRIncl_allH

//#include "types.h"

//---------------------------------------------------------------------------
//�������� ��� ����� ������
#define RAB         1  //�����
#define RAB_FAKE       12  //����� ���������
#define RAB_POSL       13  //������ �����
#define RAB_2par_AND 2 // ����� �
#define RAB_2par_OR  3 // ����� ���
#define DIAGN       4  //  �������� ��-��
#define DIAGN_2     5  //  ������� ����� ��-��
#define RASV        6  //  ������� �� - "1 - ��1 "0 - ��2
#define PROV_IF     7  //  �������� �������� (� ������������) �� "0 - ��
#define WHILE_DO    8  // ����� ����� � ������������ �� - �� "0 - ��
#define WHILE_DO_2  9999  //   �� � ������������ (�� �����������)
#define DO_UNTIL    109999 //  �������� ��������� ��� 7
#define DO_UNTIL_2  119999 //     �� ��� 5
#define DO_WHILE_DO 9 //  �� � ��������� �������� ��1 �� ��2
#define DO_WHILE_DO_2 10 // �� � ���������� ��1 - �� - ��2
#define RASV_SIM    11  // �������� ��� �������������� �����������

//�������� �������� ��������� �����
#define NO_OPEN  0    //��� ��������� �����
#define YES_OPEN 1    //���� �������� ���� (�� ����������)
#define YES_OPEN_MOD 2//���� �������� ���� (����������)

#define YES_TABLE 1  //�������� ������� �������
#define NO_TABLE  0

#define RADIUS 20 //���������� �� ������ ��� ��� ����������� ��������� ����

#define FNULL -1L //����������� ���� � �����
#define BEGIN 4L  //��������� �� ������ ������ � �����

#define CFG_NAME "graphtfe.cfg" //��� �����-������������, � ����� ������
                                //����� ���� ������, ��������� � �������� ������

#define DEC_ARH "arhive.arh" //��� �����, ��������� ����� �������

#define PROP  0 //��� ��������� ���� �������������
#define FUZZY 1

#define WIN  0 //��� ��������� ���� ���������
#define DOS 1

#define BLOCK  0 //��� ��������� ���� �����������
#define UROV 1

#define TOHN  0 //��� ��������� ������ ����������� (������ ��� �������.)
#define PRIBLJ1 1
#define PRIBLJ2 2

//��������� ��� ����������� ���� ��������� ������ �����������
#define ZAD_1 0
#define ZAD_2 1
#define ZAD_3 2
#define ZAD_4 3
#define ZAD_5 4
#define ZAD_6 5
#define NONE  6

//���� ���������
#define SIMP 0 //�������
#define COMP 1 //���������

//���� ������� ��������
#define LABOUR   0 //�������
#define CONTROL  1 //��
#define FUNCTION 2 //��
#define PROVERKA 3 //��������

#define LABOUR_T   "rab" //�������
#define CONTROL_T  "cont" //��
#define FUNCTION_T "func" //��
#define PROVERKA_T "prov" //��������

#define BB  1
#define BT  2
#define BV  3
#define BTV 4
#define BBS 5
#define BTS 6
#define BVS 7
#define BTVS 8

#endif
