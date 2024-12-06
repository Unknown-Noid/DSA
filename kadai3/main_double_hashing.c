#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "double_hashing.h"

#define B  5003
#define MAX_SEARCH 10000

typedef struct timer {
    double seconds;
    LARGE_INTEGER start_time;
    LARGE_INTEGER frequency;
    void (*reset)(struct timer *this_timer);
    void (*start)(struct timer *this_timer);
    void (*stop)(struct timer *this_timer);
    double (*result)(struct timer *this_timer);
} Timer;

void timer_reset(Timer *this_timer) {
    this_timer->seconds = 0.0;
    QueryPerformanceFrequency(&this_timer->frequency);
}
void timer_start(Timer *this_timer) { QueryPerformanceCounter(&this_timer->start_time); }
void timer_stop(Timer *this_timer) {
    LARGE_INTEGER end_time;
    QueryPerformanceCounter(&end_time);
    this_timer->seconds += (double)(end_time.QuadPart - this_timer->start_time.QuadPart) / this_timer->frequency.QuadPart;
}
double timer_result(Timer *this_timer) { return this_timer->seconds; }

int main() {
    Timer stop_watch = {0.0, {0}, {0}, timer_reset, timer_start, timer_stop, timer_result};
    stop_watch.reset(&stop_watch);

    FILE *fp = fopen("search_time.csv", "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to create file.\n");
        return EXIT_FAILURE;
    }

    DictDoubleHashing *dict = create_dict(B);
    if (dict == NULL) {
        fprintf(stderr, "Error: Unable to create dictionary.\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    int *data = (int *)malloc(B * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        delete_dict(dict);
        fclose(fp);
        return EXIT_FAILURE;
    }
    srand((unsigned)time(NULL));

    for (int i = 0; i < B; i++) {
        data[i] = ((rand() << 15) | rand()) % (B*10000) + 1; 
    }
    fprintf(fp, "Occupancy,Time(sec)\n");

    for (double occ = 0.0; occ <= 1.0; occ += 0.1) {
        int insert_count = (int)(occ * B);
        if(insert_count != 0){
            
            delete_dict(dict);
            dict = create_dict(B);

            for (int i = 0; i < insert_count; i++) {
                insert_hash(dict, data[i]);
            }

            stop_watch.reset(&stop_watch);
            stop_watch.start(&stop_watch);
            for (int i = 0; i < MAX_SEARCH; i++) {
                int target = data[rand() % insert_count];
                search_hash(dict, target);
            }
            stop_watch.stop(&stop_watch);

            double avg_time = stop_watch.result(&stop_watch) / MAX_SEARCH;
            printf("Occupancy: %.1f, Average Search Time: %.11f sec\n", occ, avg_time);
            fprintf(fp, "%.1f,%.10f\n", occ, avg_time);
        } else {

            double avg_time = 0;
            printf("Occupancy: %.1f, Average Search Time: %.11f sec\n", occ, avg_time);
            fprintf(fp, "%.1f,%.10f\n", occ, avg_time);
        }
    }

    free(data);
    delete_dict(dict);
    fclose(fp);
    printf("Program finished. Results saved to search_time.csv\n");
    return EXIT_SUCCESS;
}
