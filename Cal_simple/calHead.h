#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<queue>
#include<stack>
#include<string>
#include<string.h>
#define MAXSIZE_OF_EQUATION 256
#define _CRT_SECURE_NO_WARNINGS 

using namespace std;
//-3.14^2
/**
 * ��������ṹ���Ŀ���Ǳ��ڴ����λ���ֺ�С��
*/
typedef struct ElementsInEquation
{
    int priority;        //�������ȼ� �Ǹ�Ϊ������ -1��ʾ������
    int intPart;         //���ȼ��Ǹ�ʱ��ʾ������ASCII�� -1ʱ��ʾ����������������
    double fractionPart; // -1ʱ��ʾ��������С������
} EIE;

char* findRightParentheses(char* inputStr, char* left, int skip);
char* formatStep0(char* inputStr);
bool isComputable(char* inputStr);                                  //��������ַ����Ƿ��ܼ���
int OpCharToPriority(char ch, bool isOutOfStack);                   //�Ѳ�����ת��Ϊ��Ӧ�����ȼ�
char* findCurrentEnd(char* computableStr, char* currentElementEnd); //�ҵ���ǰEIE������λ��
EIE readSingleOPcharOrOPnum(char* computableStr, char* currentElementStart, char* currentElementEnd);//�ڿɼ�����������ʽ�ڶ���һ�����ڼ���Ĳ������������
double calculateOnce(double num1, double num2, char Opch);
queue<EIE> convertFromStrToEquation(char* computableStr);           //������ַ���ת��Ϊ���㹫ʽ
int comparePriorityOfOpChar(char chi, char cho);                    //�ȽϽ�Ҫ��ջ�Ĳ������Ͳ�����ջ�������ȼ�
double compute(char* computableStr);                        //��������ջ�ڲ������Ͳ�����
