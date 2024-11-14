#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#include "define.h"
#include "simulate.h"

int main(void)
{
    char *data_file;
    FILE *fp;

    time_t start_time, end_time;
    time_t timer;
    struct tm *local;
    int year, month, day, hour, minute, second;

    timer = time(NULL);
    local = localtime(&timer);

    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;

    printf("プログラム実行開始時刻：%d年%d月%d日 %d時%d分%d秒\n", year, month, day, hour, minute, second);

    start_time = time(NULL);

    data_file = "./result/Blocking_probability.txt";
    fp = fopen(data_file, "w");
    fclose(fp);

    for (int k = 0; k < roop_count; k++)
    {
        if ((k + 1) % 10 == 0)
        {
            printf("roop_count = %d\n", k + 1);
        }
        server_inf *server = (server_inf *)malloc(server_num * sizeof(server_inf));

        node_inf *node = (node_inf *)malloc(node_num * sizeof(node_inf));

        reset(node, server);

        srand(seed + k);

        set_poisson_distribution(node);

        if (node[node_num - 1].start_time < TIME)
        {
            printf("last node time = %lf\n", node[node_num - 1].start_time);
            printf("ノード数不足\n");
            return 0;
        }

        for (double time = 0; time <= TIME; time += dt)
        {
            simulate(node, server, time);
        }

        plot(node);

        free(server);
        free(node);
    }

    end_time = time(NULL);

    printf("実行計測時間：%lf min\n", (end_time - start_time) / 60.0);

    timer = time(NULL);
    local = localtime(&timer);

    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    day = local->tm_mday;
    hour = local->tm_hour;
    minute = local->tm_min;
    second = local->tm_sec;

    printf("プログラム実行終了時刻：%d年%d月%d日 %d時%d分%d秒\n", year, month, day, hour, minute, second);

    return 0;
}