#include <stdio.h>
#include <stdlib.h>

// Find the greatest common divisor of the two integers, n and m.
int gcd_recursive(int n, int m) {

    if (n < m) {
        int tmp = m;
        m = n;
        n = tmp;
    }
    if (m == 0) { 
        return n;
    } else {
        return gcd_recursive(m, n%m);
    }
    return n;
}