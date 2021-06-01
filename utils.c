#include "utils.h"

int v3_copy(const double *from, double *to) {
    int i;
    for (i = 0; i < 3; i++) {
        to[i] = from[i];
    }
    return 0;
}

int v3_div(double *n, const double *d) {
    int i;
    for (i = 0; i < 3; i++) {
        if (d[i] == 0)
            return 1; // fail
        n[i] /= d[i];
    }
    return 0;
}

int v3_cross(const double *A, const double *B, double *C) {
    C[0] = A[1] * B[2] - A[2] * B[1];
    C[1] = A[2] * B[0] - A[0] * B[2];
    C[2] = A[0] * B[1] - A[1] * B[0];
    return 0;
}

double v3_dot(const double *A, const double *B) {
    int i;
    double sum = 0;
    for (i = 0; i < 3; i++) {
        sum += A[i] * B[i];
    }
    return sum;
}

int v3_subv(double *A, const double *B) {
    int i;
    for (i = 0; i < 3; i++) {
        A[i] -= B[i];
    }
    return 0;
}

int v3_addv(double *A, const double *B) {
    int i;
    for (i = 0; i < 3; i++) {
        A[i] += B[i];
    }
    return 0;
}

int v3_scmult(double *A, double sc) {
    int i;
    for (i = 0; i < 3; i++) {
        A[i] *= sc;
    }
    return 0;
}