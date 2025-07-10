#include <stdio.h>

int main() {
    int numbers[6] = {1, 2, 3, 4, 5, 6};
    int *pointer = numbers;

    int sum = 0;
    int i = 0;
    while (i < 5) {
        sum += numbers[i++];
    }
    
    printf("%d", sum);
    return 0;
}