#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char name[1900],name2[1900],key1[1800],key2[1800],k;
	int i,flag=1,n,len,len1,len2,h;
	scanf("%s",&name);
	scanf("%s",&key1);
	scanf("%s",&key2);
	len=strlen(name);
	len1=strlen(key1);
	len2=strlen(key2);
	
	if(len<6){
		n=5;
		printf("error%d",n);
		exit(0);
	}else if(len>18) {
		n=6;
		printf("error%d",n);
		exit(0);
	}
	
	if(strcmp(key1,key2)!=0){
		n=12;
		printf("error%d",n);
		exit(0);
	}
	
	if(len1<6){
		n=13;
		printf("error%d",n);
		exit(0);
	}else if(len1>16) {
		n=14;
		printf("error%d",n);
		exit(0);
	}
	
	for(i=1;i<len;i++){
		if((name[0]<='Z'&&name[0]>='A')||
			(name[0]<='z'&&name[0]>='a')){
			if((name[i]<='Z'&&name[i]>='A')||
				(name[i]<='z'&&name[i]>='a')||
				(name[i]<='9'&&name[i]>='0')||
				name[i]=='_'||name[i]=='@'||name[i]=='.'){
					continue;
			}else{
				n=7;
				printf("error%d",n);
				exit(0);
			}
		}else {
			n=8;
			printf("error%d",n);
			exit(0);
		}
	}
	int j;
	flag=0;
	for(i=(len-1);i>=(len-8);i--){
		if((name[i]=='.')){
			for(j=i;j>=(len-8);i--){
				if(name[i]=='@'){	
					flag=1;break;
				}else flag=0;
			}
		}else flag=0;
	}
	if(flag==0){
		n=10;
		printf("error%d",n);
		exit(0);
	}
	printf("succeed");
	return 0;
 } 
