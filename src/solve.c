#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "solve.h"
#include "city.h"

#define NUM_INITIAL_SOLUTIONS 100

static double calc_dist_diff(const City *city, int *route, int n, int i, int j) {
    int prev_i = (i == 0) ? route[n-1] : route[i-1];
    int next_i = (i == n-1) ? route[0] : route[i+1];
    int prev_j = (j == 0) ? route[n-1] : route[j-1];
    int next_j = (j == n-1) ? route[0] : route[j+1];

    double current = distance(city, route[i], prev_i) + 
                     distance(city, route[i], next_i) +
                     distance(city, route[j], prev_j) +
                     distance(city, route[j], next_j);

    double new_dist = distance(city, route[j], prev_i) +
                      distance(city, route[j], next_i) +
                      distance(city, route[i], prev_j) +
                      distance(city, route[i], next_j);

    return new_dist - current;
}

static double calc_total_distance(const City *city, int *route, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        sum += distance(city, route[i], route[next]);
    }
    // デバッグ用
    printf("%lf\n", sum);
    return sum;
}

static void generate_initial_route(int *route, int n) {
    for (int i = 0; i < n; i++) route[i] = i;
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = route[i];
        route[i] = route[j];
        route[j] = temp;
    }
}

static Answer local_search(const City *city, int *initial_route, int n) {
    int *current_route = (int *)malloc(sizeof(int) * n);
    memcpy(current_route, initial_route, sizeof(int) * n);

    double current_distance = calc_total_distance(city, current_route, n);
    bool improved;

    // デバッグ用
    int iteration_count = 0;
    const int MAX_ITER = 100000;

    do {
        improved = false;
        double best_diff = 0.0;
        int best_i = -1, best_j = -1;

        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                double diff = calc_dist_diff(city, current_route, n, i, j);
                if (diff < best_diff) {
                    best_diff = diff;
                    best_i = i;
                    best_j = j;
                }
            }
        }

        if (best_i != -1 && best_j != -1) {
            int temp = current_route[best_i];
            current_route[best_i] = current_route[best_j];
            current_route[best_j] = temp;
            current_distance += best_diff;
            improved = true;
        }

        // デバッグ用
        iteration_count++;
        if (iteration_count > MAX_ITER) {
            fprintf(stderr, "Too many iterations!\n");
            break;
        }
    } while (improved);

    Answer ans = {current_distance, current_route};
    return ans;
}

Answer solve(const City *city, int n) {
    srand(time(NULL));
    Answer best_answer = {1e5, NULL};

    for (int i = 0; i < NUM_INITIAL_SOLUTIONS; i++) {
        int *initial_route = (int *)malloc(sizeof(int) * n);
        generate_initial_route(initial_route, n);

        Answer local_best = local_search(city, initial_route, n);

        if (local_best.dist < best_answer.dist) {
            if (best_answer.route != NULL) free(best_answer.route);
            best_answer = local_best;
        } else {
            free(local_best.route);
        }

        free(initial_route);
    }

    return best_answer;
}