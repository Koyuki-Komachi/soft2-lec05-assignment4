#pragma once
#include "city.h"

typedef struct ans{
    double dist;
    int *route;
} Answer;

Answer solve(const City *city, int n);


