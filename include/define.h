#ifndef DEFINE_H
#define DEFINE_H

// パラメータ類
#define server_num 3
#define TIME 10000
#define lambda 0.1
#define node_num 1300
#define mu 0.05
#define dt 0.1
#define seed 1101
#define roop_count 10

typedef struct
{
    int usingflag;
} server_inf;

typedef struct
{
    int ready;
    int service_server_num;
    double start_time;
    double holding_time;
    int block_flag;
    int service_done;
} node_inf;

#endif