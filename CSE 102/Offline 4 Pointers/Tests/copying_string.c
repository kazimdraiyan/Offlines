#include <stdio.h>

int main() {
    char source[100];
    scanf("%s", source);

    char destination[100];
    char *sp = source;
    char *dp = destination;
    while (*sp) {
        *dp++ = *sp++;
    }
    *dp = 0;
    printf("%s", destination);
}