#include"calHead.h"

using namespace std;

int main()
{

    char inputStr[MAXSIZE_OF_EQUATION];
    while (true)
    {
        cout << "����";
        cout << "\n��������ʽ:";
        cin.getline(inputStr, MAXSIZE_OF_EQUATION, '\n');
        if (isComputable(inputStr))
        {
            cout << "\n������Ϊ:" << compute(inputStr) << endl;
        }
        else
            break;
        memset(inputStr, 0, sizeof(char));  //LD:������˵��ԭ����inputStr������𣿵�������������˼��ֻ����һλ��ֵ��
        cout << "�����������\n����q���ûس�����������" << endl;
        if (getchar() == 'q') { break; }
    }
    return 0;
}

