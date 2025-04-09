#include <stdio.h>

stuct A{
    int a;
    char b;
};

int main(){
    printf("fnn");
    struct A a;
    a.a = 1;
    a.b = 'b';
    printf("%d %c", a.a, a.b);
}

