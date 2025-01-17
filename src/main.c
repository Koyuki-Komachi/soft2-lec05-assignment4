#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // for assert()
#include <unistd.h> // for sleep()
#include <string.h> // for memset()
#include "city.h"
#include "map.h"
#include "solve.h"

int main(int argc, char**argv)
{
    // const による定数定義
    const int width = 70;
    const int height = 40;
    const int max_cities = 100;
    
    Map *map = init_map(width, height);
    
    if (argc != 2){
        fprintf(stderr, "Usage: %s <city file>\n", argv[0]);
        exit(1);
    }
    int n = 1;
    City *city = load_cities(argv[1],&n);
    assert( n > 1 && n <= max_cities); // さすがに都市数100は厳しいので

    // 町の初期配置を表示
    plot_cities(map, city, n, NULL);
    sleep(1);

    // 訪れる順序を記録する配列を設定
    int *route = (int*)calloc(n, sizeof(int));

    const Answer ans = solve(city, n);
    memcpy(route, ans.route, sizeof(int) * n);
    plot_cities(map, city, n, route);
    printf("total distance = %f\n", ans.dist);
    for (int i = 0 ; i < n ; i++){
	printf("%d -> ", route[i]);
    }
    printf("0\n");

    // 動的確保した環境ではfreeをする
    free(route);
    free(city);
    
    return 0;
}
