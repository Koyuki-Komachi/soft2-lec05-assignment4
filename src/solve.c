#include "solve.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "map.h"

double solve(const City *city, int n, int *route, int *visited) {
    route[0] = 0;  // 循環した結果を避けるため、常に0番目からスタート
    visited[0] = 1;

    Answer ans = search(city, n, route, visited);

    memcpy(route, ans.route, sizeof(int) * n);
    free(ans.route);
    return ans.dist;
}

Answer search(const City *city, int n, int *route, int *visited) {
    int start = 0;
    // 訪問した個数を数える
    for (int i = 1; i < n; i++) {
        if (!route[i]) {
            start = i;
            break;
        }
    }
    // 全て訪問したケース（ここが再帰の終端条件）
    if (start == 0) {
        double sum_d = 0;
        for (int i = 0; i < n; i++) {
            const int c0 = route[i];
            const int c1 = route[(i + 1) % n];  // nは0に戻る
            sum_d += distance(get_city(city, c0), get_city(city, c1));
        }
        int *retarg = (int *)malloc(sizeof(int) * n);
        memcpy(retarg, route, sizeof(int) * n);

        return (Answer){.dist = sum_d, .route = retarg};
    }

    // 特定の分岐における最小の巡回経路を調べる
    Answer min = {.dist = 10000000000, .route = NULL};
    for (int i = 1; i < n; i++) {
        // 未訪問なら訪れる
        if (!visited[i]) {
            if (i == 2 && !visited[1]) continue;  // 逆順の巡回経路を抑制

            route[start] = i;
            visited[i] = 1;

            Answer tmp = search(city, n, route, visited);

            // 最小の巡回経路かどうか確認
            if (tmp.dist < min.dist) {
                free(min.route);
                min = tmp;
            } else {
                free(tmp.route);
            }

            route[start] = 0;
            visited[i] = 0;
        }
    }

    return min;
}
