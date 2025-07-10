#include <stdio.h>

// Checks if a number is prime
int main() {
    int sum;
    scanf("%d", &sum);
    
    int is_prime = 0;
    if (sum > 1) {
        is_prime = 1;
        for (int i = 2; i * i <= sum; i++) {
            if (sum % i == 0) {
                is_prime = 0;
                break;
            }
        }
    }

    printf("%d", is_prime);

    return 0;
}
