#include<stdio.h>
#include<math.h>

void inc(int b[],int n)  //将b表示的二进制数增1
{
  int i;
  for(i=0;i<n;i++)   //遍历数组b
  {   if(b[i])           //将元素1改为0
         b[i]=0;
       else              //将元素0改为1并退出for循环
      {  b[i]=1;
          break;
      }
  }
}

void PSet(int a[],int b[],int n)  //求幂集 
{ int i,j;
  int pw=(int)pow(2,n);           //求2^n
  printf("1~%d的幂集：\n",n);
  
  for(i=0;i<pw;i++)               //执行2^n次 
  {
  	printf(" { ");
  	int k;
  	for(k=0;k<n;k++)          //执行n次 
  	if(b[k])
  	printf("%d",a[k]);
  	printf(" } ");
  	inc(b,n);                     //b表示的二进制数增1 
  }
  printf("\n");
}

int main(){
	int n=3,i;
	int a[10],b[10];
	for(i=0;i<n;i++)
	{
		a[i]=i+1;
		b[i]=0;
	 } 
	 PSet(a,b,n);
} 

