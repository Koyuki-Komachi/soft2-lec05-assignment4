#include "solve.h"

#include <stdio.h>
#include <stdlib.h>

#include "city.h"
#include "map.h"

double solve(const City *city, int n, int *route, int *visited) {
    // 以下はとりあえずダミー。ここに探索プログラムを実装する
    // 現状は町の番号順のルートを回っているだけ
    // 実際は再帰的に探索して、組み合わせが膨大になる。
    route[0] = 0;  // 循環した結果を避けるため、常に0番目からスタート
    visited[0] = 1;
    for (int i = 0; i < n; i++) {
        route[i] = i;
        visited[i] = 1;  // 訪問済みかチェック
    }

    // トータルの巡回距離を計算する
    // 実際には再帰の末尾で計算することになる
    double sum_d = 0;
    for (int i = 0; i < n; i++) {
        const int c0 = route[i];
        const int c1 = route[(i + 1) % n];  // nは0に戻る
        sum_d += distance(get_city(city, c0), get_city(city, c1));
    }
    return sum_d;
}
