#include <stdio.h>
#include <stdbool.h>
#define N 10

bool QQQ(int t, int a[N][N]) {
	int i,j;
    int d[N] = {0};
    if (t==1) { 
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                d[i] += a[i][j];
            }
        }
    } else if (t== 2) { 
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                d[i] += a[i][j]; 
                d[j] -= a[i][j]; 
            }
        }
    }
    for (i = 0; i < N; i++) {
        if (d[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int t,i,j,a[N][N];
    scanf("%d", &t);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    bool result = QQQ(t, a);
    if (result) {
        printf("True");
    } else {
        printf("False");
    }
    return 0;
}

