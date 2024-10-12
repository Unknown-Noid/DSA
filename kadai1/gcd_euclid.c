#include <stdio.h>
#include <stdlib.h>

// Find the greatest common divisor of the two integers, n and m.
int gcd_euclid(int n, int m) {

    if (n < m) {
        int tmp;
        n = tmp;
        n = m;
        m = tmp;
    }
    int i = 1;
    int gcd;
    while (i <= n) {
        if (n%i == 0 && m%i == 0)
            gcd = i;
        i = i+1;
    }


    return n;
}