#include <stdio.h>

int main() {
    int numbers1[5] = {1, 2, 3, 4, 5};
    int numbers2[5];

    int *ip1 = numbers1;
    int *ip2 = numbers2;

    while (ip1 <= &numbers1[4]) {
        *ip2++ = *ip1++;
    }

    for (int i = 0; i < 5; i++) {
        printf("%d\n", numbers2[i]);
    }

    return 0;
}