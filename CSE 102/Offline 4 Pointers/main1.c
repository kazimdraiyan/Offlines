#include <stdio.h>
#include <stdlib.h>

void exitOnError()
{
    printf("Memory allocation failed.");
    exit(1);
}

void removeNegatives(int *input, int n, int **output, int *newSize)
{
    *newSize = 0;
    // Determining how many non-negative numbers are there.
    for (int i = 0; i < n; i++)
    {
        if (*(input + i) >= 0)
        {
            (*newSize)++;
        }
    }
    if (*newSize == 0)
    {
        *output = NULL;
        return;
    }

    *output = (int *)malloc(*newSize * sizeof(int));

    if (*output == NULL)
    {
        exitOnError();
    }

    for (int i = 0, j = 0; i < n; i++)
    {
        if (*(input + i) >= 0)
        {
            *(*output + j) = *(input + i);
            j++;
        }
    }
}

int main()
{
    int n, newSize;
    scanf("%d", &n);

    int *inputPointer = (int *)malloc(n * sizeof(int));
    int *outputPointer;

    if (inputPointer == NULL)
    {
        exitOnError();
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", inputPointer + i);
    }

    removeNegatives(inputPointer, n, &outputPointer, &newSize);

    printf("%d\n", newSize);
    for (int i = 0; i < newSize; i++)
    {
        printf("%d ", *(outputPointer + i));
    }

    free(inputPointer);
    free(outputPointer);

    return 0;
}