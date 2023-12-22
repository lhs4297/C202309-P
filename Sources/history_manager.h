#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <time.h>

#define MAX_HISTORY_COUNT 100
#define MAX_PATH_LENGTH 256

typedef struct {
    char old_path[MAX_PATH_LENGTH];
    char new_path[MAX_PATH_LENGTH];
    time_t moved_time;
} History;

typedef struct {
    History histories[MAX_HISTORY_COUNT];
    int count;
} HistoryManager;

void init_history_manager(HistoryManager* history_manager);
void add_history(HistoryManager* history_manager, const char* old_path, const char* new_path, time_t moved_time);
void print_histories(const HistoryManager* history_manager);
void save_history(HistoryManager* history_manager, const char* filename);

#endif