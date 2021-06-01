#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int iterate(double *M, double *B, double *T, double g, double dt) {
    double G[3];
    v3_cross(M, B, G); // G = M x B
    v3_scmult(G, g); //   G = g * (M x B)

    double M0[3] = {0,0,1};
    double rel[3];
    v3_copy(M, rel); // rel = M
    v3_subv(rel, M0); // rel = M - M0
    v3_div(rel, T); // rel = (M - M0)/T

    double dMdt[3];
    v3_copy(G, dMdt); // dMdt = g*(MxB)
    v3_subv(dMdt, rel); // dMdt = g*(MxB) - (M - M0)/T

    v3_scmult(dMdt, dt); // dMdt = dMdt * dt

    v3_addv(M, dMdt); // M = M + dM
    return 0;
}

//run_sim(bfn, out, &g, T, &dt);

int run_sim(FILE *bf, FILE *out, double *g, double *T, double *dt) {
    double time = 0;

    double M[3] = {0, 0, 1};
    double B[3] = {0, 0, 0};

    char line[255];
    int len = 255;

    double a, b, c;
    int k;

    fprintf(out, "%f %lf %lf %lf\n", time, M[0], M[1], M[2]);

    while (fgets(line, len, bf)) {
        if (line[0] == '%')
            continue;
        k = sscanf(line, "%lf %lf %lf\n", &a, &b, &c);
        if (k != 3)
            continue;
        B[0] = a;
        B[1] = b;
        B[2] = c;

        time += *dt;
        iterate(M, B, T, *g, *dt);
        fprintf(out, "%f %lf %lf %lf\n", time, M[0], M[1], M[2]);
        //int iterate(double *M, double *B, double *T, double g, double dt) {
    }
}

int read(const char *fn, char *bfn, char *ofn, double *g, double *T, double *dt) {
    FILE *fp = NULL;
    char line[255];
    int len=255;
    char arg[255], val[255];
    fp = fopen(fn, "r");

    if (fp == NULL) {
        printf("File %s not found\n", fn);
        return 1;
    }

    strcpy(bfn, "");
    strcpy(ofn, "");
    *g = 0;
    T[0] = 1000;
    T[1] = 1000;
    T[2] = 1000;
    *dt = 0.001;
    double T2 = 0, T1 = 0;
    int k = 0;
    while (fgets(line, len, fp)) {
        if (line[0] == '%')
            continue;
        k = sscanf(line, "%s %s\n", arg, val);
        if (k != 2)
            continue;
        if (strncmp(arg, "bfn", 3) == 0) {
            strcpy(bfn, val);
        } else if (strncmp(arg, "g", 1) == 0) {
            *g = atof(val);
        } else if (strncmp(arg, "T2", 2) == 0){
            T2 = atof(val);
        } else if (strncmp(arg, "T1", 2) == 0){
            T1 = atof(val);
        } else if (strncmp(arg, "dt", 2) == 0) {
            *dt = atof(val);
        } else if (strncmp(arg, "output", 6) == 0) {
            strcpy(ofn, val);
        }
    }
    T[0] = T2;
    T[1] = T2;
    T[2] = T1;
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");

    double M[3] = {0, 0, 1};
    double B[3] = {0, 0, 0};

    int i;
    double T[3] = {1000, 1000, 1000};
    double g = 0;
    double dt = 0.0001;
    char ofn[255], bfn[255];
    for (i = 1; i < argc; i++) {
        read(argv[i], bfn, ofn, &g, T, &dt);
    }

    printf("BFN: %s\nOFN: %s\ng: %f\ndt: %f\nT: [%f %f %f]\n", bfn, ofn, g, dt, T[0], T[1], T[2]);

    FILE *bf = NULL;
    if (strcmp(bfn, "") == 0) {
        printf("Please pass BField\n");
        return 1;
    }
    bf = fopen(bfn, "r");
    if (bf == NULL) {
        printf("Reading %s failed\n", bfn);
        return 1;
    }

    FILE *out = stdout;
    if (strcmp(ofn, "") != 0) {
        out = fopen(ofn, "w");
        if (out == NULL) {
            printf("Failed to open %s, outputting to stdout.\n", ofn);
            out = stdout;
        }
    }

    run_sim(bf, out, &g, T, &dt);

    fclose(out);
    fclose(bf);
    return 0;
}


// dM/dt = g(M * B) - ((M - M0) / T)