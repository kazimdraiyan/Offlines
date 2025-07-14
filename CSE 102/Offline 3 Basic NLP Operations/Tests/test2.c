#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define N 5

// Input buffer test

// Returns 1 if any meaningful user input is in the buffer.
int clear_input_buffer(char *last_inputted_str_by_fgets)
{
    int meaningful_char_count_in_buffer = 0;
    if (last_inputted_str_by_fgets == NULL || last_inputted_str_by_fgets[strlen(last_inputted_str_by_fgets) - 1] != '\n')
    {
        // If the pointer is null, then it is assumed that the input was taken by scanf, so there's at least a \n in the input buffer. In this case, the RHS of the || operator does not get evaluated.
        // If the pointer is not null, then it is assumed that the input was taken by fgets. In this case, if the last character (in front of \0) is not \n, then there's at least a \n in the input buffer.
        char temp;
        do
        {
            temp = getchar();
            printf("GETCHAR:%d:%c:MEW\n", temp, temp);
            if (!isspace(temp))
            {
                printf("MEW MEW MEW\n");
                meaningful_char_count_in_buffer++;
            }
        } while (temp != '\n');
    }
    return meaningful_char_count_in_buffer > 0;
}

int main() {
    char command[N];
    scanf("%4s", command);
    printf("HOIT: %d\n", command[-2]);
    printf("%d\n", clear_input_buffer(NULL));
}