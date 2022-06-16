#include <stdio.h>

void caller(int (*cc)(int ),int a) {
    cc(a);
}

int blub(int a) {
    printf("%i", a); 
    return 1;
}

int main()
{
    caller(blub, 1000);
    return 1;
}