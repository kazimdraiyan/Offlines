#include <stdio.h>

int main()
{
    int n, total_energy = 0;
    scanf("%d", &n);

    for (int row_index = 1; row_index <= n; row_index++)
    {
        int k, energy_level = 0;
        scanf("%d", &k);

        // No input will be negative, so odd_sum, even_sum, sum can't be negative
        int odd_sum = 0;
        int even_sum = 0;

        for (int cell_index = 1; cell_index <= k; cell_index++)
        {
            int num;
            scanf("%d", &num);

            if (cell_index % 2 == 1)
                odd_sum += num;
            else
                even_sum += num;
        }

        int sum = odd_sum + even_sum;

        // Checks if prime
        int is_prime_active = 0;
        if (sum > 1) // Any number that's less than or equal to 1 is not prime by default
        {
            is_prime_active = 1;
            for (int i = 2; i * i <= sum; i++)
            {
                if (sum % i == 0)
                {
                    is_prime_active = 0;
                    break;
                }
            }
        }

        // Checks if palindrome
        int is_palindrome_active = 1;
        int test_sum = sum;
        // Edge Case: if the sum is a single digit integer (0-9), the loop won't run, deciding the sum as an pallindrome
        while (test_sum > 9)
        {
            int first_digit_place_weight = 1; // Example: the weight of the first digit place of the number 123 is 100
            int first_digit = test_sum;
            // Removes the last digit of the sum until only 1 digit remains, which is the first digit
            while (first_digit > 9)
            {
                first_digit /= 10;
                first_digit_place_weight *= 10; // Increases the weight variable by the factor of 10 each time the last digit gets removed
            }

            int last_digit = test_sum % 10;

            // Edge Case: if the test_sum becomes a single digit integer (0-9), the first_digit and the last_digit are the same, deciding the test_sum as a pallindrome
            if (first_digit != last_digit)
            {
                is_palindrome_active = 0;
                break;
            }
            test_sum = (test_sum - first_digit * first_digit_place_weight) / 10; // Removes the first and the last digit of the test_sum
        }

        // Check if harmonic and/or balanced
        int is_harmonic = (odd_sum - even_sum) % 7 == 0; // ..., -14, -7, 0 are also considered as divisible by 7
        int is_balanced = odd_sum == even_sum;

        int active_status = is_prime_active + is_palindrome_active + is_harmonic + is_balanced;

        if (is_prime_active)
            energy_level += 5;
        if (is_palindrome_active)
            energy_level += 3;
        if (is_harmonic)
            energy_level += 4;
        if (is_balanced)
            energy_level += 2;

        total_energy += energy_level;

        if (active_status == 0)
            printf("Row %d: INACTIVE - Energy Level %d", row_index, energy_level);
        else if (active_status == 1)
            printf("Row %d: LOW - Energy Level %d", row_index, energy_level);
        else if (active_status == 2)
            printf("Row %d: MEDIUM - Energy Level %d", row_index, energy_level);
        else if (active_status == 3)
            printf("Row %d: HIGH - Energy Level %d", row_index, energy_level);
        else
            printf("Row %d: ULTRA - Energy Level %d", row_index, energy_level);

        printf("\n");
    }
    printf("Total Energy: %d", total_energy);

    return 0;
}
