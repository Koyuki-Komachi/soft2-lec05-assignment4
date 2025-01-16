#pragma once
#include "city.h"

typedef struct ans{
    double dist;
    int *route;
} Answer;

double solve(const City *city, int n, int *route, int *visited);

Answer search(const City *city, int n, int *route, int *visited);


