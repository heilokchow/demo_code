#include <iostream>
#include <stdio.h>

const int ret(const int* const* const a, int n) {
    int s = 0;
    //int** a0 = a;
    /*a[0] = new int[n];
    for (int i = 0; i < n; i++) {
        a[0][i] = 0;
    }*/
    //a0[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            s += a[i][j];
        }
    }
    return s;
}
int main() {
    int n = 3;
    int** k = new int* [n];
    for (int i = 0; i < n; i++) {
        k[i] = new int[n];
        for (int j = 0; j < n; j++) k[i][j] = 1;
    }
    const int m = ret(k, n);
    //m++;
    printf("sum is %d\n", m);

    for (int i = 0; i < n; i++) delete[] k[i];
    delete[] k;
    return 0;
}