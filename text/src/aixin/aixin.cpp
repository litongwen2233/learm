#include"aixin.h"

using namespace std;

void Display_aixin(void)
{
    //爱心曲线方程 (x^2 + y^2 - a)^3 - x^2*y^3 = 0
    const double a = 0.5;
    //定义绘图边界
    const double bound = 1.3*sqrt(a);
    //x,y坐标变化步距
    const double step = 0.05;
    //二维扫描所有点
    for(double y = bound;y >= -bound;y -= step)
    {
        for(double x = -bound ; x <= bound ; x +=0.5*step )
        {
            if((pow((pow(x,2) + pow(y,2) -a ),3) - pow(x,2)*pow(y,3)) <= 0)
                cout << "*";
            else
                cout << " ";
        }
        cout<<endl;
    }
    // cin.get();
}