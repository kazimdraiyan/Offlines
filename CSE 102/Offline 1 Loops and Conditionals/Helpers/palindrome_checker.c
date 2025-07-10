#include <stdio.h>

int main() {
    int sum;
    
    scanf("%d", &sum);

    // Check if palindrome
    int is_palindrome_active = 1;
    int test_sum = sum;
    printf("%d\n", test_sum);
    while (test_sum > 9) {
        int first_digit_place_weight = 1;
        int first_digit = test_sum;
        while (first_digit > 9) {
            first_digit /= 10;
            first_digit_place_weight *= 10;
        }

        int last_digit = test_sum % 10;
        
        test_sum = (test_sum - first_digit * first_digit_place_weight) / 10; // Removes the first and the last digit of the test_sum
        printf("%d\n", test_sum);
        if (first_digit != last_digit) {
            is_palindrome_active = 0;
            break;
        }
    }

    printf("%d", is_palindrome_active);

    return 0;
}