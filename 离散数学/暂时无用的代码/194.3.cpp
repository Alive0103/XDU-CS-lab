#include<string.h>
#include<iostream>
using namespace std;

char *A,*B,*F;
int a,b,f;


int Judge(char *A,char*B,char*F){
    int i,j,k;
    for(i=1;i<a;i=i+2){
        k=0;
        for(j=2;j<f;j+=6){
                if(F[j]==A[i])
                        k++;
        }
        if(k==0||k>1)
                return 0;
    }
    return 1;
}

int ds(char*A,char*B,char*F){
    int i,j;
    for(i=4;i<b;i=i+6)
        for(j=4;j<f;j=j+6)
        if(F[i]==F[j]&&F[i-2]!=F[j-2])return 0;
    return 1;
}

int ms(char*A,char*B,char*F){
        int i,j;
        for(i=1;i<b;i=i+2){
                for(j=4;j<f;j=j+6)
                        if(F[j]==B[i])break;
                if(j>f)return 0;
        }
        return 1;
}


int main(){
    A=new char;
    B=new char;
    F=new char;
    cout<<"输入集合A："<<endl;
    cin>>A;
    cout<<"输入集合B："<<endl;
    cin>>B;
    cout<<"输入A到B的关系："<<endl;
    cin>>F;
    a=strlen(A);
    b=strlen(B);
    f=strlen(F);
    cout<<"集合"<<A<<"到"<<B<<"的一个关系是："<<F<<endl;
    if(!Judge(A,B,F)){
        cout<<"不满足函数定义！"<<endl;
    }
    else if(ds(A,B,F)&&ms(A,B,F)){
        cout<<"此为双射！"<<endl;
    }
    else if(ds(A,B,F))cout<<"此为单射"<<endl;
    else if(ms(A,B,F))cout<<"此为满射"<<endl;
    else cout<<"二者皆不是！"<<endl;


return 0;
}


