#include <stdio.h>
#include <stdlib.h>

void bitwise_operations(int n, char* string1, char* string2) {
	int i; 
    char* result_and = (char*)malloc((n + 1) * sizeof(char));
    char* result_xor = (char*)malloc((n + 1) * sizeof(char));
    char* result_or = (char*)malloc((n + 1) * sizeof(char));

    for ( i = 0; i < n; i++) {
        
        if (string1[i] == '1' && string2[i] == '1') {
            result_and[i] = '1';
        } else {
            result_and[i] = '0';
        }
        if (string1[i] != string2[i]) {
            result_xor[i] = '1';
        } else {
            result_xor[i] = '0';
        }
        if (string1[i] == '1' || string2[i] == '1') {
            result_or[i] = '1';
        } else {
            result_or[i] = '0';
        }

        
    }

    result_and[n] = '\0';
    result_xor[n] = '\0';
    
    result_or[n] = '\0';

    printf("%s\n%s\n%s\n", result_and, result_or, result_xor);

    free(result_and);
    free(result_or);
    free(result_xor);
}

int main() {
    int N;
    scanf("%d", &N);

    char* string1 = (char*)malloc((N + 1) * sizeof(char));
    char* string2 = (char*)malloc((N + 1) * sizeof(char));

    scanf("%s", string1);
    scanf("%s", string2);

    bitwise_operations(N, string1, string2);

    free(string1);
    free(string2);

    return 0;
}

