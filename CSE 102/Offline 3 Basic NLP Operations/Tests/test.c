#include <stdio.h>
#include <string.h>

void clear_input_buffer(char *last_inputted_str_by_fgets)
{
    if (last_inputted_str_by_fgets == NULL || last_inputted_str_by_fgets[strlen(last_inputted_str_by_fgets) - 1] != '\n') {
        // If the pointer is null, then it is assumed that the input was taken by scanf, so there's at least a \n in the input buffer. In this case, the RHS of the || operator does not get evaluated.
        // If the pointer is not null, then it is assumed that the input was taken by fgets. In this case, if the last character (in front of \0) is not \n, then there's at least a \n in the input buffer.
        printf("there is something in the buffer\n");
        char temp;
        do {
            temp = getchar();
        } while (temp != '\n');
    }
}

// fgets behavior
int main() {
    char command[5];

    scanf("%4s", command);
    clear_input_buffer(NULL);
    
    printf("INPUT TAKEN\n%s\nSTRING PRINTED\n", command);

    // printf("%d:%c:MEW\n", command[0], command[0]);
    // printf("%d:%c:MEW\n", command[1], command[1]);
    // printf("%d:%c:MEW\n", command[2], command[2]);
    // printf("%d:%c:MEW\n", command[3], command[3]);
    // printf("%d:%c:MEW\n", command[4], command[4]); // Defined behavior till this
    // printf("%d:%c:MEW\n", command[5], command[5]);
    // printf("%d:%c:MEW\n", command[6], command[6]);
    // printf("%d:%c:MEW\n", command[7], command[7]);
    // printf("%d:%c:MEW\n", command[8], command[8]);
    // printf("%d:%c:MEW\n", command[9], command[9]);
    // printf("%d:%c:MEW\n", command[10], command[10]);

    printf("MEW MEW MEW\n");
    char from_buffer = getchar();
    printf("GETCHAR:%d:%c:MEW", from_buffer, from_buffer);

    return 0;
}
