#include <stdio.h>
#include <stdlib.h>

// Find the greatest common divisor of the two integers, n and m.
int gcd_euclid(int n, int m) {
    if (n < m) {
        int tmp = m;
        m = n;
        n = tmp;
    }
    while (m != 0) {
        int r = n % m;
        n = m;
        m = r;
    }
    return n;
}