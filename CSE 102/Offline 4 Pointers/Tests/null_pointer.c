#include <stdio.h>

// Dereferencing a NULL pointer crashes the program, because the OS kills the process.
int main() {
    int *p = NULL;
    printf("hoit%dhoit", *p);
    return 0;
}