#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#include "define.h"
#include "simulate.h"

void reset(node_inf *node, server_inf *server)
{
    for (int h = 0; h < node_num; h++)
    {
        node[h].ready = 0;
        node[h].service_server_num = 1000;
        node[h].start_time = 0;
        node[h].holding_time = 0;
        node[h].block_flag = 0;
        node[h].service_done = 0;
    }

    for (int h = 0; h < server_num; h++)
    {
        server[h].usingflag = 0;
    }
}

void set_poisson_distribution(node_inf *node)
{
    double r = (double)rand() / (RAND_MAX + 1.0);
    node[0].start_time = -(1 / lambda) * log(r);
    r = (double)rand() / (RAND_MAX + 1.0);
    node[0].holding_time = -(1 / mu) * log(r);

    for (int h = 1; h < node_num; h++)
    {
        r = (double)rand() / (RAND_MAX + 1.0);
        node[h].start_time = node[h - 1].start_time + (-(1 / lambda) * log(r));
        r = (double)rand() / (RAND_MAX + 1.0);
        node[h].holding_time = -(1 / mu) * log(r);
        // printf("[%d]time = %lf\n", h, node[h].start_time);
    }

    // printf("time = %lf\n", node[node_num - 1].start_time);
}

void simulate(node_inf *node, server_inf *server, double time)
{
    for (int h = 0; h < node_num; h++)
    {
        if (node[h].ready == 1)
        {
            node[h].holding_time -= dt;
            if (node[h].holding_time <= 0)
            {
                node[h].ready = 0;
                server[node[h].service_server_num].usingflag = 0;
            }
        }
    }

    int not_using_server_num = server_num + 1;
    for (int h = 0; h < node_num; h++)
    {
        if (node[h].start_time - time <= 0.001 && node[h].service_done == 0)
        {
            for (int i = 0; i < server_num; i++)
            {
                if (server[i].usingflag == 0)
                {
                    not_using_server_num = i;
                }
            }

            if (not_using_server_num > server_num)
            {
                node[h].block_flag = 1;
                node[h].service_done = 1;
            }
            else
            {
                node[h].ready = 1;
                node[h].service_server_num = not_using_server_num;
                server[not_using_server_num].usingflag = 1;
                node[h].service_done = 1;
            }
        }
    }
    int s;
    s = 0;
}

void plot(node_inf *node)
{
    char *data_file;
    FILE *fp;

    data_file = "./result/Blocking_probability.txt";
    fp = fopen(data_file, "a");
    int blocking_node_counter = 0, service_done_flag = 0;
    for (int h = 0; h < node_num; h++)
    {
        if (node[h].block_flag == 1)
        {
            blocking_node_counter++;
        }
        if (node[h].service_done == 1)
        {
            service_done_flag++;
        }
    }

    double Ps = 0.0, Ps_denominator = 0.0, Ps_numerator;

    for (int h = 0; h <= server_num; h++)
    {
        Ps_denominator += (pow((lambda / mu), (double)h)) / (double)kaijo(h);
    }

    Ps_numerator = pow((lambda / mu), (double)server_num) / (double)kaijo(server_num);

    Ps = Ps_numerator / Ps_denominator;

    // printf("Ps = %lf\n", Ps);

    // printf("block_count = %d\n", blocking_node_counter);
    // printf("service_count = %d\n", service_done_flag);
    fprintf(fp, "%lf\t%lf\n", (double)((double)blocking_node_counter / (double)service_done_flag), Ps);
    fclose(fp);
}

int kaijo(int num)
{
    int count = num;

    if (num == 0)
    {
        return 1;
    }

    int result = 1;
    while (count > 0)
    {
        result *= count;
        count--;
    }

    return result;
}