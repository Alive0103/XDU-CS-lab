#include<string.h>
#include<iostream>
using namespace std;
char *A,*B,*C;
int a,b,c;
int Ju(char *A,char*B,char*C){
    int i,j,k;
    for(i=1;i<a;i=i+2){
        k=0;
        for(j=2;j<c;j+=6){
            if(C[j]==A[i]){
            	k++;
			}
        }
        if(k==0||k>1)
        	return 0;
		
    }
    return 1;
}

int isInjection(char*A,char*B,char*C){
    int i,j;
    for(i=4;i<b;i=i+6){
    	for(j=10;j<c;j=j+6){
    		if(C[i]==C[j]&&C[i-2]!=C[j-2]){
    			return false;
			}
		}
	}
    return true;
}

int isSurjection(char*A,char*B,char*C){
    int i,j,k=0;
        for(i=1;i<b;i=i+2){
        	k=0;
            for(j=4;j<c;j=j+6){
                if(C[j]==B[i]){
                	k++;
				} 
			}
			if(k==0) {
                return 0;
			}
        }
    return 1;
}


int main(){
    A=new char;
    B=new char;
    C=new char;
    cin>>A;
    cin>>B;
    cin>>C;
    a=strlen(A);
    b=strlen(B);
    c=strlen(C);
    if(!Ju(A,B,C)){
    	cout<<A<<" -> "<< B << ":nf"<<endl;
	}
    if(Ju(A,B,C)==1){
        if(isInjection(A,B,C)==1 &&isSurjection(A,B,C)==1){
        	cout<<A<<" -> "<< B << ":s"<<endl;
    	}
    	else if(isInjection(A,B,C)==1 &&isSurjection(A,B,C)!=1) {
    		cout<<A<<" -> "<< B << ":d"<<endl;
		}
    	else if(isInjection(A,B,C)!=1 &&isSurjection(A,B,C)==1) {
    		cout<<A<<" -> "<< B << ":m"<<endl;
		}
    	else {
    		cout<<A<<" -> "<< B << ":f"<<endl;
		}
    }
	return 0;
}


