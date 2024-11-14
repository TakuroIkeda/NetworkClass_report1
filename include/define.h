#ifndef DEFINE_H
#define DEFINE_H

#define server_num 4
#define TIME 10000
#define lambda 1
#define node_num 10300
#define mu 0.05
#define dt 0.1
#define seed 1101
#define roop_count 100

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