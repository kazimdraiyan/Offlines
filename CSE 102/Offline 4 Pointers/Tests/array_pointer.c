#include <stdio.h>

int main() {
    int nums[5] = {1, 2, 3, 4, 5};
    int *p = nums;
    int *q = &nums[0];
    int *r = &nums; // &nums is different
    printf("%p\n", p);
    printf("%p\n", q);
    printf("%p\n", r);
    return 0;
}