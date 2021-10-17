#include"calHead.h"

using namespace std;

/**
* 找到匹配的右括号
* @param char* 原字符串首地址
* @param char* 左括号地址
* @param int 查找时需要跳过的右括号个数；
*/
char* findRightParentheses(char* inputStr, char* left, int skip)
{
    for (char* temp = left + 1; (*temp) != '\0'; temp++)
    {
        if ((*temp) == ')')
        {
            if (!skip)
            {
                return temp;//skip为0 遇见右括号即为找到
            }
            else
            {
                skip--;
            }
        }
        else
        {
            if ((*temp) == '(')
            {
                skip++;
                return findRightParentheses(inputStr, temp, skip);
            }
        }
    }
}

/**
* 规范输入的字符串的格式，其中包括：删去空格，转化sqrt()为幂形式，给字符串末尾加上"="
* @param char* 输入的字符串
* @return 修改后的原字符串地址
*/
char* formatStep0(char* inputStr)
{

    string newStrTemp;
    if (*inputStr == '-')
    {
        newStrTemp.push_back('0');//当待计算的字符串以-开头 在前面加上操作数0
    }
    for (char* temp = inputStr; (*temp) != '\0'; temp++)
    {
        if ((*temp) != ' ')
        {
            if ((*temp) == 's') //这里是否需要判断用户输入的内容是否是sqrt而不是其他的以s开头的命令？
            {
                char* tempEndOfSqrt = temp;
                char* tempRight = findRightParentheses(inputStr, temp + 4, 0);
                for (temp = temp + 4; temp <= tempRight; temp++)
                {
                    if ((*temp) != ' ')
                    {
                        newStrTemp.push_back(*temp);
                    }
                }
                newStrTemp += "^(0.5)";
                temp--;//这里不减一会少读一位
            }
            else
            {
                newStrTemp.push_back(*temp);
            }
        }
    }
    if (newStrTemp.back() != '=') { newStrTemp.push_back('='); }
    //用户输不输入=都可以
    memset(inputStr, 0, sizeof(inputStr));
    strcpy(inputStr, newStrTemp.c_str());

    return inputStr;

}

/**
* 判断用户输入的字符串是否可以运行
 * @param inputStr 输入的字符串
 * @return 可以运行返回true
*/
bool isComputable(char* inputStr)
{
    /**
     *check
     * 括号不成对 递归找
     * /0
     * 小数点后还有小数点 +1.23.45+
     * ...
     */
    if (strlen(inputStr) == 0) { return false; }
    return true;
}

/**
 * @param ch 要求优先级的字符
 * @param isOutOfStack 是否要返回栈外优先级
 * @return 对应优先级
 * @author sxz
*/
int OpCharToPriority(char ch, bool isOutOfStack)
{
    switch (ch)
    {
    case '+': return isOutOfStack ? 2 : 3; break;
    case '-': return isOutOfStack ? 2 : 3; break;
    case '*': return isOutOfStack ? 4 : 5; break;
    case '/': return isOutOfStack ? 4 : 5; break;
    case '%': return isOutOfStack ? 4 : 5; break;
    case '(': return isOutOfStack ? 8 : 1; break;
    case ')': return isOutOfStack ? 1 : 8; break;
    case '^': return isOutOfStack ? 6 : 7; break;
    case '&': return isOutOfStack ? 6 : 7; break;
    case '=': return 0; break;  //LD：需要一个default
    }
}

/**
 * @author sxz
 * @param chi 栈顶字符
 * @param cho 栈外字符
 * @return
 * 1    若栈内优先级低于栈外优先级
 * 0    若栈内优先级高于栈外优先级
 * -1   若栈内优先级等于栈外优先级
*/
int comparePriorityOfOpChar(char chi, char cho)
{
    if (OpCharToPriority(chi, false) < OpCharToPriority(cho, true))
        return 1;
    else
    {
        if (OpCharToPriority(chi, false) > OpCharToPriority(cho, true))
            return 0;
        else
            return -1;
    }
}

/**
 * @param computableStr 要计算的字符串
 * @param currentElementEnd 当前EIE开始地址
 * @return char* 当前EIE结束的地址
 * @author sxz
*/
char* findCurrentEnd(char* computableStr, char* currentElementEnd)
{
    char* temp = currentElementEnd;
    if ((*temp < '0' || *temp > '9'))
    {
        return currentElementEnd; //此时指向的是一个操作符
    }
    else//是temp指向数字数字或在字符串开头
    {

        bool hasFraction = false;
        bool finished = false;
        for (; !finished; temp++)
        {
            if (*(temp + 1) < '0' || *(temp + 1) > '9')
            {//找到了非数字，在之前格式化为算式字符串后这里只能是操作符
                if (hasFraction)
                { //曾找到过小数点
                    finished = true;
                }
                else
                { //未读到过小数点
                    if (*(temp + 1) == '.')
                        hasFraction = true;
                    else
                        finished = true;
                }
            }
        }
        return temp - 1;
    }
}

/**
 * @param computableStr 要计算的字符串
 * @param currentElementStart 现在所指的数字最高位地址
 * @return 一个ELE, 用于计算的一个数字(int or double)或者一个操作符
 * @author sxz
 */
EIE readSingleOPcharOrOPnum(char* computableStr, char* currentElementStart, char* currentElementEnd)
{
    EIE temp;
    if (currentElementStart == currentElementEnd)
    { //为单个操作符或单个数字
        if (*currentElementStart < '0' || *currentElementStart>'9')
        {
            temp.intPart = (int)(*currentElementStart);
            temp.fractionPart = 0;
            temp.priority = OpCharToPriority(*currentElementStart, true);
        }
        else
        {
            temp.intPart = (int)(*currentElementStart - 48);
            temp.fractionPart = 0;
            temp.priority = -1;
        }

    }
    else//读到的是一个长数字或者小数
    {
        int sumOfIntPart = 0;//整数部分
        char* readerPtr;//工作指针
        for (readerPtr = currentElementStart; readerPtr <= currentElementEnd; readerPtr++)
        {
            if (!isdigit(*readerPtr))
                break;
            else
                sumOfIntPart = sumOfIntPart * 10 + (int)((*readerPtr) - 48);
        }
        char* dot = readerPtr;
        if (readerPtr != currentElementEnd)
        {
            double sumOfFractionPart = 0.0;
            readerPtr++;
            for (; readerPtr <= currentElementEnd; readerPtr++)
            {
                sumOfFractionPart += ((*readerPtr) - 48) * pow(0.1, (readerPtr - dot) / sizeof(char));
            }
            temp.intPart = sumOfIntPart;
            temp.fractionPart = sumOfFractionPart;
            temp.priority = -1;
        }
        else//
        {
            temp.intPart = sumOfIntPart;
            temp.fractionPart = 0.0;
            temp.priority = -1;
        }

    }
    return temp;
}

/**
* 计算一次操作数栈顶两个数和操作符栈顶一个操作符
* @param double
* 1-2
* 12
* -
* 21
*/
double calculateOnce(double num1, double num2, char Opch)
{
    switch (Opch)
    {
    case('+'):return num1 + num2; break;
    case('-'):return num2 - num1; break;
    case '*': return num2 * num1; break;
    case '/': return num2 / num1; break;
    case '%': return (int)num2 % (int)num1; break;
    case '^': return pow(num2, num1); break;
    case '&': return pow(num2, 1.0 / num1); break;
    default:break;
    }

}

/**
 * @param computableStr 用于计算的字符串
 * @return EIE数组形式的算式
 * @author sxz
*/
queue<EIE> convertFromStrToEquation(char* computableStr)
{
    queue<EIE> result;
    string str = computableStr;


    for (char* currentElementStart = computableStr;
        currentElementStart < computableStr + strlen(computableStr);
        currentElementStart++)
    {
        char* currentElementEnd = currentElementStart;
        //初始化指向当前EIE结束的指针
        currentElementEnd = findCurrentEnd(computableStr, currentElementEnd);
        /*cout << &currentElementStart << "\t" << *currentElementStart << endl;
        cout << &currentElementEnd << "\t" << *currentElementEnd<<endl;*/
        //指向当前EIE结束的地址
        result.push(readSingleOPcharOrOPnum(computableStr, currentElementStart, currentElementEnd));
        //把读好的一个EIE放入数组形式的算式
        //优化：和上一步一起操作，节约时间
        currentElementStart = currentElementEnd;
        //工作指针指向下一个EIE前一位
    }
    return result;
}

/**
@param char* 可计算的字符串公式
@return double 计算结果
*/
double compute(char* computableStr)
{
    stack<double> opnd;//操作数
    stack<char> optr;//操作符
    cout << formatStep0(computableStr) << endl;
    queue<EIE> equation = convertFromStrToEquation(formatStep0(computableStr));
    while (!equation.empty())
    {//保证equation队列不为空
        if (!opnd.empty())
        {
            cout << "opnd.top:" << (opnd.top()) << endl;
        }
        else { cout << "empty" << endl; }

        if (equation.front().priority == -1)
        {
            opnd.push(equation.front().intPart + equation.front().fractionPart);
            equation.pop();
            //若为数字,将其push进操作数栈(opnd), 继续处理下一个字符
        }
        else//此时为操作符
        {

            if (optr.empty())
            {//保证操作符栈在接下来不为空
                if (equation.front().intPart == '=') { break; }
                optr.push((char)(equation.front().intPart));
                equation.pop();
                if (optr.top() == '(' && equation.front().priority == OpCharToPriority('-', true))
                {
                    opnd.push(0);//括号后和算式最开始的减号需要补0操作数
                }
            }
            else
            {
                switch (comparePriorityOfOpChar(optr.top(), equation.front().intPart))
                {
                case(1):
                {
                    optr.push(equation.front().intPart);
                    equation.pop();
                    if (optr.top() == '(' && equation.front().priority == OpCharToPriority('-', true))
                    {
                        opnd.push(0);//括号后和算式最开始的减号需要补0操作数
                    }
                    break;
                }
                case(0):
                {
                    if (opnd.size() > 1)
                    {
                        double num1 = opnd.top();
                        opnd.pop();
                        double num2 = opnd.top();
                        opnd.pop();
                        opnd.push(calculateOnce(num1, num2, optr.top()));
                        optr.pop();
                    }
                    break;
                }
                case(-1):
                {
                    optr.pop();
                    equation.pop();
                    break;
                }
                default:break;
                }
            }
        }
    }
    return opnd.top();
}
