#include <stdio.h>
#include <string.h>
#include <ctype.h>

// strncpy test

int main() {
    char names[][50] = {"Alice", "Bob", "Charlie"};

    for (int i = 0; i < 3; i++) {
        char *name = names[i];
        names[i][0] = '\0';
        strncpy(names[i], name, 2);
    }

    for (int i = 0; i < 3; i++) {
        printf("Name %d: %s\n", i + 1, names[i]);
    }

    return 0;
}