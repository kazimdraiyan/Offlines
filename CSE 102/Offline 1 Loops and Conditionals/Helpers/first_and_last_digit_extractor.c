#include <stdio.h>

// Given a non-negative integer, this tool extracts the first and the last digit of a number
// Leading 0s are ignored
// For single digit integers [0-9], the first digit = the last digit = the integer
int main() {
    int sum;
    scanf("%d", &sum);
    
    int last_digit = sum % 10;

    int first_digit = sum;
    while (!(first_digit >= 0 && first_digit <= 9)) {
        first_digit /= 10;
    }

    printf("%d %d", first_digit, last_digit);

    return 0;
}
