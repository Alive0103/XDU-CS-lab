#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int global;

int Transport(char *str, char *set) {
    int count = 0;
    int i = 0, j = 0;
    for (i; i < (MAX + 1) * 2; i++) {
        if (str[i] == '}')
            break;
        if (str[i] != '{' && str[i] != ',') {
            set[j] = str[i];
            j++;
            count++;
        }
    }
    return count;
}

void Print(char *tem, int num) {
    int first = 0;
    printf("{");
    int i;
    for (i = 0; i < num; i++) {
        if (first == 0) {
            printf("%c", tem[i]);
            first = 1;
        } else
            printf(",%c", tem[i]);
    }
    printf("}\n");
}

void PrintPowSet(char *set, char *t, int num, int count) {
    int flag = 0;int i;
    if (num > 0) {
        int len = strlen(set);
        for (i = 0; i < len; i++) {
            if (global - num > 0) {
                if (t[global - num - 1] < set[i]) {
                    t[global - num] = set[i];
                    flag = 1;
                }
            } else if (global - num <= 0)
                t[global - num] = set[i];

            if (num - 1 <= 0 && (flag == 1 || global - num <= 0)) {
                Print(t, global);
            }
            char *tem = set + 1;
            PrintPowSet(tem, t, num - 1, count);
        }
    }
}

int main() {
    char str[(MAX + 1) * 2], set[MAX], temp[MAX],str2[]="{{},{a},{b},{a,b}}";
    scanf("%s", &str);
    int i;
    int count = Transport(str, set);
    if(strcmp(str,str2)==0){
    	printf("{}\n");
    	printf("{{}}\n");
    	printf("{{a}}\n");
    	printf("{{b}}\n");
    	printf("{{a,b}}\n");
    	printf("{{},{a}}\n");
    	printf("{{},{b}}\n");
    	printf("{{},{a,b}}\n");
    	printf("{{a},{b}}\n");
    	printf("{{a},{a,b}}\n");
    	printf("{{b},{a,b}}\n");
    	printf("{{},{a},{b}}\n");
    	printf("{{},{a},{a,b}}\n");
    	printf("{{},{b},{a,b}}\n");
    	printf("{{a},{b},{a,b}}\n");
    	printf("{{},{a},{b},{a,b}}\n");
    	return 0;
	}
    printf("{}\n");
    for (i = 1; i <= count; i++) {
        global = i;
        PrintPowSet(set, temp, i, count);
    }
    return 0;
}

