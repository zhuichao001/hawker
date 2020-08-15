#include <stdio.h>


//greatest common divisor
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a%b);
    }
}


//least common multiple
int lcm(int a, int b) {
    int k = gcd(a, b);
    return (a/k)*b;
}


int main() {
    int d = gcd(15,20);
    printf("gcd:%d\n", d);
    int m = lcm(15,20);
    printf("lcm:%d\n", m);
    return 0;
}
