#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* formatLongNumber(long num) {
    int num_digits = snprintf(NULL, 0, "%ld", num);
    
    char* formatted_num = (char*)malloc(num_digits + num_digits/3 + 2); 
    
    if (formatted_num == NULL) {
        printf("Không d? b? nh?!\n");
        exit(EXIT_FAILURE);
    }
    
    snprintf(formatted_num, num_digits + 1, "%ld", num);
    
    int i, j;
    for (i = num_digits - 3, j = num_digits; i > 0; i -= 3, j++) {
        memmove(formatted_num + i + 1, formatted_num + i, j - i);
        formatted_num[i] = ' ';
    }
    
    return formatted_num;
}

int main() {
    long num;
    printf("Nhap so: ");
    scanf("%ld", &num);
    
    char* formatted_num = formatLongNumber(num);
    printf("Ket qua: %s\n", formatted_num);
    
    free(formatted_num);
    
    return 0;
}


