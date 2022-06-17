#include <stdio.h>

void caller(int (*cc)(int ),int a) {
    cc(a);
}

int foo(int a) {
    printf("%i", a); 
    return 1;
}

int main()
{
    caller(foo, 1000);
    return 1;
}