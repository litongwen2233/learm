#include"string_text.h"
#include<iostream>

using namespace std;

void string_text_(void)
{
    string st0;
    string st1("THe expence of spirit");
    string st2("123456");
    char *str = "I am string form C";
    string str_C = str + string("++");
    const char *str_ = st1.c_str(); 
    cout<<"st0 = "<<st0<<","<<"st1 = "<<st1<<",st2 = "<<st2<<endl;
    string st3 = st1 + st2;
    cout<<"s3 = st1 + st2 = "<<st3<<endl;
    const int buffsize = 344;
    if(st0.empty())
    {
        cout<<"st0 = NULL"<<endl;
    }
    cout<<"The is string of C:"<<str<<",Convert into a C++:"<<str_C<<endl;

}