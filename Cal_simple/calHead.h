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
 * 定义这个结构体的目的是便于储存多位数字和小数
*/
typedef struct ElementsInEquation
{
    int priority;        //计算优先级 非负为操作符 -1表示操作数
    int intPart;         //优先级非负时表示操作符ASCII码 -1时表示操作数的整数部分
    double fractionPart; // -1时表示操作数的小数部分
} EIE;

char* findRightParentheses(char* inputStr, char* left, int skip);
char* formatStep0(char* inputStr);
bool isComputable(char* inputStr);                                  //检查读入的字符串是否能计算
int OpCharToPriority(char ch, bool isOutOfStack);                   //把操作符转化为对应的优先级
char* findCurrentEnd(char* computableStr, char* currentElementEnd); //找到当前EIE结束的位置
EIE readSingleOPcharOrOPnum(char* computableStr, char* currentElementStart, char* currentElementEnd);//在可计算的算术表达式内读出一个用于计算的操作数或操作符
double calculateOnce(double num1, double num2, char Opch);
queue<EIE> convertFromStrToEquation(char* computableStr);           //读入的字符串转换为计算公式
int comparePriorityOfOpChar(char chi, char cho);                    //比较将要入栈的操作符和操作符栈顶的优先级
double compute(char* computableStr);                        //计算两个栈内操作数和操作符
