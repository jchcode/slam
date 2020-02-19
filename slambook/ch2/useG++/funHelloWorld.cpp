#include <iostream>
#include "libFunction.h"	// 使用此声明是该自定义函数调用了"libFunction.h"中的printHSLAM()

using namespace std;

void printHCPlus2();

void printHWorld()
{
    cout << "hello, world" << endl;

    printHCPlus2();
    printHSLAM();

    return;
}

void printHCPlus2()
{
    cout << "hello, cplusplus" << endl;

    return;
}
