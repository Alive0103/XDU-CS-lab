#include <iostream>
using namespace std;

//递归实现求一个集合的全部子集
//思路：将字符串中的所有字符的状态看作0或1.
//template <class T>
void subset(int *p,int n,int len){

    //基本情况
    if (n==0){

        int j = 0;
        cout<<"{";
        for (int i = 0; i < len; ++i) {//用len来控制全部输出字符
            if (j!=0&&p[i]!=0){
                cout<<",";//控制，的输出
            }
            if (p[i]!=0){
                cout<<p[i];
                j++;
            }
        }

        cout<<"}"<<endl;
        return;
    }

    for (int j = 0; j <=1; ++j) {//每个元素都有0和1两种状态

        int *ch = new int[len];

        for (int i = 0; i < len; ++i) {
            ch[i] = p[i];//创建临时数组来储存p的所有值,确保还能输出元素的初始值
        }

        if (j==0){
            ch[n-1] = 0;//0表示元素不在该子集中
        }

        subset(ch,n-1,len);//判断剩下的n-1个字符是否在子集中

    }
    

}

