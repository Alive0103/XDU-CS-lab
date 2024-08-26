#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义最大输入长度
#define MAX_INPUT_LENGTH 1000

// 定义函数类型
typedef struct {
    int* domain;  // 定义定义域数组
    int domainSize;  // 定义域大小
    int* codomain;  // 值域数组
    int codomainSize;  // 值域大小
    int** relation;  // 关系数组
    int relationSize;  // 关系大小
} Function;

// 函数声明
Function* createFunction(int domainSize, int codomainSize);
void destroyFunction(Function* function);
void parseSet(char* input, int** set, int* setSize);
void parseRelation(char* input, Function* function);
int isFunction(Function* function);
int isInjection(Function* function);
int isSurjection(Function* function);

int main() {
    char input[MAX_INPUT_LENGTH];

    // 输入集合A
    fgets(input, MAX_INPUT_LENGTH, stdin);
    int* setA;
    int setSizeA;
    parseSet(input, &setA, &setSizeA);

    // 输入集合B
    fgets(input, MAX_INPUT_LENGTH, stdin);
    int* setB;
    int setSizeB;
    parseSet(input, &setB, &setSizeB);

    // 输入关系R
    fgets(input, MAX_INPUT_LENGTH, stdin);
    Function* function = createFunction(setSizeA, setSizeB);
    parseRelation(input, function);

    // 判断函数类型
    if (isFunction(function)) {
    	int i;
        if (isInjection(function) && isSurjection(function)) {
            printf("{ ");
            for (i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:s\n");
        } else if (isInjection(function)) {
            printf("{ ");
            for ( i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:d\n");
        } else if (isSurjection(function)) {
            printf("{ ");
            for ( i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for (i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:m\n");
        } else {
            printf("{ ");
            for (i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:f\n");
        }
    } else {
        printf("{ ");
        int i;
        for (i = 0; i < setSizeA; i++) {
            printf("%d ", setA[i]);
        }
        printf("} -> { ");
        for (i = 0; i < setSizeB; i++) {
            printf("%d ", setB[i]);
        }
        printf("}:nf\n");
    }

    // 释放内存
    destroyFunction(function);
    free(setA);
    free(setB);

    return 0;
}

// 创建函数
Function* createFunction(int domainSize, int codomainSize) {
    Function* function = (Function*)malloc(sizeof(Function));
    function->domain = (int*)malloc(sizeof(int) * domainSize);
    function->domainSize = domainSize;
    function->codomain = (int*)malloc(sizeof(int) * codomainSize);
    function->codomainSize = codomainSize;
    function->relation = NULL;
    function->relationSize = 0;
    return function;
}

// 销毁函数
void destroyFunction(Function* function) {
	int i;
    free(function->domain);
    free(function->codomain);
    for ( i = 0; i < function->relationSize; i++) {
        free(function->relation[i]);
    }
    free(function->relation);
    free(function);
}

// 解析集合
void parseSet(char* input, int** set, int* setSize) {
    char* token = strtok(input, "{}, \n");
    int count = 0;
    *setSize = 0;
    while (token != NULL) {
        (*setSize)++;
        token = strtok(NULL, "{}, \n");
    }

    *set = (int*)malloc(sizeof(int) * (*setSize));
    token = strtok(input, "{}, \n");
    while (token != NULL) {
        (*set)[count] = atoi(token);
        count++;
        token = strtok(NULL, "{}, \n");
    }
}

// 解析关系
void parseRelation(char* input, Function* function) {
    char* token = strtok(input, "<>, \n");
    int count = 0;
    function->relationSize = 0;
    while (token != NULL) {
        (function->relationSize)++;
        token = strtok(NULL, "<>, \n");
    }

    function->relation = (int**)malloc(sizeof(int*) * function->relationSize);
    token = strtok(input, "<>, \n");
    while (token != NULL) {
        function->relation[count] = (int*)malloc(sizeof(int) * 2);
        function->relation[count][0] = atoi(token);
        token = strtok(NULL, "<>, \n");
        function->relation[count][1] = atoi(token);
        count++;
        token = strtok(NULL, "<>, \n");
    }
}

// 判断是否为函数
int isFunction(Function* function) {
	int i,j;
    for (i = 0; i < function->domainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][0] == function->domain[i]) {
                count++;
            }
        }
        if (count != 1) {
            return 0;
        }
    }
    return 1;
}

// 判断是否为单射
int isInjection(Function* function) {
	int i,j;
    for (i = 0; i < function->domainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][0] == function->domain[i]) {
                count++;
            }
        }
        if (count > 1) {
            return 0;
        }
    }
    return 1;
}

// 判断是否为满射
int isSurjection(Function* function) {
	int i,j;
    for (i = 0; i < function->codomainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][1] == function->codomain[i]) {
                count++;
            }
        }
        if (count == 0) {
            return 0;
        }
    }
    return 1;
}

