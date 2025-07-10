#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.c"

#define MAX_SIZE 100000
#define MAX_BINS 1000
#define MAX_STARS 50

void print_help(void)
{
    printf("Commands:\n");
    printf("  set     - Set array size, seed, and distribution (uniform or gaussian)\n");
    printf("  min     - Print minimum value\n");
    printf("  max     - Print maximum value\n");
    printf("  mean    - Print mean value\n");
    printf("  median  - Print median value\n");
    printf("  stddev  - Print standard deviation\n");
    printf("  hist    - Plot histogram\n");
    printf("  summary - Print min, max, mean, stddev\n");
    printf("  help    - Show this help message\n");
    printf("  exit    - Exit the program\n");
}

void formatted_print(char *description, double value)
{
    printf("%-10s: %10.4lf\n", description, value);
}

void clear_input_buffer(void)
{
    // Characters remain in the input buffer if a string larger than expected is inputted, or a string is inputted where an integer was expected. The following loop clears the buffer.
    char c;
    do
    {
        c = getchar();
    } while (c != '\n');
}

int compare(const void *num1_pointer, const void *num2_pointer)
{
    // Casting void (can be of any type) pointer to double pointer, then getting the value from the pointer.
    double num1 = *(double *)num1_pointer;
    double num2 = *(double *)num2_pointer;

    if (num1 < num2)
        return -1;
    else if (num1 > num2)
        return 1;
    else
        0;
}

int main()
{
    double array[MAX_SIZE];
    int size = 0;
    int is_array_initialized = 0;
    double min, max, mean, median, stddev;

    print_help();

    char command[8];           // The longest command name is 'summary' which consists of 7 chars.
    char distribution_type[9]; // The longest distribution name is 'gaussian' which consists of 8 chars.
    while (1)
    {
        printf("\nEnter command: ");
        scanf("%7s", &command);
        clear_input_buffer();

        if (!strcmp(command, "set"))
        {
            // Clearing garbage values or values from the previous iteration is not necessary
            unsigned int seed;

            printf("Enter number of elements (<= %d): ", MAX_SIZE);
            scanf("%d", &size);
            clear_input_buffer();

            if (size < 1 || size > MAX_SIZE)
            {
                printf("Invalid distribution.\n");
                continue;
            }

            printf("Enter seed: ");
            scanf("%u", &seed);
            clear_input_buffer();

            printf("Distribution? (uniform/gaussian): ");
            scanf("%8s", distribution_type);
            clear_input_buffer();

            if (!strcmp(distribution_type, "uniform"))
            {
                double input_min, input_max;
                printf("Enter min and max: ");
                scanf("%lf %lf", &input_min, &input_max);
                clear_input_buffer();

                populate_array_uniform(array, size, input_min, input_max, seed);
                is_array_initialized = 1;
                printf("Array initialized with uniform distribution.\n");
            }
            else if (!strcmp(distribution_type, "gaussian"))
            {
                double input_mean, input_stddev;
                printf("Enter mean and stddev: ");
                scanf("%lf %lf", &input_mean, &input_stddev);
                clear_input_buffer();

                populate_array_gaussian(array, size, input_mean, input_stddev, seed);
                is_array_initialized = 1;
                printf("Array initialized with gaussian distribution.\n");
            }
            else
            {
                printf("Invalid distribution.\n");
                continue;
            }
            if (is_array_initialized)
            {

                // Finding min, max and mean
                min = array[0];
                max = array[0];
                double sum = array[0];
                for (int i = 1; i < size; i++)
                {
                    sum += array[i];
                    if (array[i] < min)
                    {
                        min = array[i];
                    }
                    else if (array[i] > max)
                    {
                        max = array[i];
                    }
                }
                mean = sum / size;

                // Finding standard deviation
                double square_sum = 0;
                for (int i = 0; i < size; i++)
                {
                    double deviation = mean - array[i];
                    square_sum += deviation * deviation;
                }
                stddev = sqrt(square_sum / size);

                // Finding median
                qsort(array, size, sizeof(double), compare);
                if (size % 2 == 1)
                {
                    median = array[(size - 1) / 2];
                }
                else
                {
                    median = (array[size / 2 - 1] + array[size / 2]) / 2;
                }
            }
        }
        else if (!is_array_initialized && (!strcmp(command, "min") || !strcmp(command, "max") || !strcmp(command, "mean") || !strcmp(command, "median") || !strcmp(command, "stddev") || !strcmp(command, "summary") || !strcmp(command, "hist")))
        {
            printf("Array not initialized. Use 'set' command first.\n");
        }
        else if (!strcmp(command, "min"))
        {
            formatted_print("Min", min);
        }
        else if (!strcmp(command, "max"))
        {
            formatted_print("Max", max);
        }
        else if (!strcmp(command, "mean"))
        {
            formatted_print("Mean", mean);
        }
        else if (!strcmp(command, "median"))
        {
            formatted_print("Median", median);
        }
        else if (!strcmp(command, "stddev"))
        {
            formatted_print("Std Dev", stddev);
        }
        else if (!strcmp(command, "summary"))
        {
            formatted_print("Min", min);
            formatted_print("Max", max);
            formatted_print("Mean", mean);
            formatted_print("Median", median);
            formatted_print("Std Dev", stddev);
        }
        else if (!strcmp(command, "hist"))
        {
            int number_of_bins = 0;
            printf("Enter number of bins: ");
            scanf("%d", &number_of_bins);
            clear_input_buffer();

            if (number_of_bins < 1 || number_of_bins > MAX_BINS)
            {
                printf("Invalid number of bins. Must be between 1 and %d.\n", MAX_BINS);
                continue;
            }

            double bin_width = (max - min) / number_of_bins;
            int bin_counts[MAX_BINS] = {0};

            for (int i = 0; i < size; i++)
            {
                int idx = (array[i] - min) / bin_width;
                if (idx == number_of_bins)
                {
                    idx--; // Including the max value to the last bin
                }
                bin_counts[idx]++;
            }
            int max_count = bin_counts[0];
            for (int i = 1; i < number_of_bins; i++)
            {
                if (bin_counts[i] > max_count)
                {
                    max_count = bin_counts[i];
                }
            }
            double scaling_factor = max_count > MAX_STARS ? MAX_STARS / (float)max_count : 1;

            double from = min;
            for (int i = 0; i < number_of_bins; i++)
            {
                printf("[%6.2lf - %6.2lf]: ", from, from + bin_width);
                int scaled_bin_count = (int)(bin_counts[i] * scaling_factor);
                for (int j = 0; j < scaled_bin_count; j++)
                {
                    printf("*");
                }
                from += bin_width;
                printf("\n");
            }
        }
        else if (!strcmp(command, "help"))
        {
            print_help();
        }
        else if (!strcmp(command, "exit"))
        {
            break;
        }
        else
        {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
    return 0;
}