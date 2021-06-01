#ifndef BLOCH_UTILS
#define BLOCH_UTILS

int v3_copy(const double *from, double *to);
int v3_div(double *n, const double *d);
int v3_cross(const double *A, const double *B, double *C);
double v3_dot(const double *A, const double *B);
int v3_subv(double *A, const double *B);
int v3_addv(double *A, const double *B);
int v3_scmult(double *A, double sc);

#endif
