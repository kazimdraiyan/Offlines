#include <stdio.h>
#include <stdlib.h>

void exitOnError()
{
    printf("Memory allocation failed.");
    exit(1);
}

int compare(char *word1, char *word2)
{
    while (*word1 != '.' && *word2 != '.')
    {
        if (*word1 < *word2)
            return -1;
        else if (*word1 > *word2)
            return 1;
        word1++;
        word2++;
    }

    // Lexicographically, shorter string comes first.
    if (*word1 == '.' && *word2 != '.')
        return -1;
    else if (*word1 != '.' && *word2 == '.')
        return 1;

    return 0;
}

void bubbleSort(char **words, int n)
{
    for (int swapUntil = n - 1; swapUntil >= 1; swapUntil--) // Reduces the swapping area from the end
    {
        for (int i = 0; i < swapUntil; i++) // This is for swapping each contiguous pairs in the swapping area
        {
            int comparison = compare(*(words + i), *(words + i + 1));
            if (comparison > 0)
            {
                char *temp = *(words + i);
                *(words + i) = *(words + i + 1);
                *(words + i + 1) = temp;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    char **words = (char **)malloc(n * sizeof(char *));
    if (words == NULL)
    {
        exitOnError();
    }

    for (int i = 0; i < n; i++)
    {
        *(words + i) = (char *)malloc(27 * sizeof(char)); // Maximum length of a word is 25. Extra 2 is for the trailing full stop and the null terminator.
        if (*(words + i) == NULL)
        {
            exitOnError();
        }

        scanf("%s", *(words + i));
    }

    bubbleSort(words, n);

    for (int i = 0; i < n; i++)
    {
        printf("%s\n", *(words + i));
    }

    for (int i = 0; i < n; i++)
    {
        free(*(words + i));
    }
    free(words);

    return 0;
}