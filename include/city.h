#pragma once
#include <stddef.h>

typedef struct city City;

double distance(const City *city, int i, int j);
City *load_cities(const char* filename,int *n);

City *get_city(const City *a, size_t i);

int get_x(const City *c);
int get_y(const City *c);
