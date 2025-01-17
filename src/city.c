#include "city.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// 町の構造体（今回は2次元座標）を定義
struct city {
    int x;
    int y;
};

double distance(const City *city, int i, int j) {
    const double dx = city[i].x - city[j].x;
    const double dy = city[i].y - city[j].y;
    return sqrt(dx * dx + dy * dy);
}

City *load_cities(const char *filename, int *n) {
    City *city;
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "%s: cannot open file.\n", filename);
        exit(1);
    }
    fread(n, sizeof(int), 1, fp);
    city = (City *)malloc(sizeof(City) * *n);

    for (int i = 0; i < *n; i++) {
        fread(&city[i].x, sizeof(int), 1, fp);
        fread(&city[i].y, sizeof(int), 1, fp);
    }
    fclose(fp);
    return city;
}

City *get_city(const City *a, size_t i) { return a + i; }

int get_x(const City *c) { return c->x; }

int get_y(const City *c) { return c->y; }
