#pragma once
// 描画用
#include "city.h"

typedef struct map Map;

void draw_line(Map *map, const City *a, const City *b);
void draw_route(Map *map, const City *city, int n, const int *route);
void plot_cities(Map *map, const City *city, int n, const int *route);

Map *init_map(const int width, const int height);
void free_map_dot(Map m);
