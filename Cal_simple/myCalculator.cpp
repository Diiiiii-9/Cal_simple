#include"calHead.h"

using namespace std;

int main()
{

    char inputStr[MAXSIZE_OF_EQUATION];
    while (true)
    {
        cout << "界面";
        cout << "\n请输入表达式:";
        cin.getline(inputStr, MAXSIZE_OF_EQUATION, '\n');
        if (isComputable(inputStr))
        {
            cout << "\n计算结果为:" << compute(inputStr) << endl;
        }
        else
            break;
        memset(inputStr, 0, sizeof(char));  //LD:这里是说把原本的inputStr给清空吗？第三个参数的意思是只给第一位赋值吗？
        cout << "按任意键继续\n输入q按敲回车键结束计算" << endl;
        if (getchar() == 'q') { break; }
    }
    return 0;
}

