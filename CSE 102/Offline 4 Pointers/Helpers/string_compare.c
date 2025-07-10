#include <stdio.h>
#include <string.h>

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

int main()
{
    printf("%d\n", strcmp("mewing streak", "mewing streal"));
    printf("%d\n", compare("mewing streak.", "mewing streal."));
}