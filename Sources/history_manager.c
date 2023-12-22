#include <stdio.h>
#include <string.h>
#include "history_manager.h"


void init_history_manager(HistoryManager* history_manager) {
    history_manager->count = 0;
}

void add_history(HistoryManager* history_manager, const char* old_path, const char* new_path, time_t moved_time) {
    if (history_manager->count >= MAX_HISTORY_COUNT) {
        fprintf(stderr, "�����丮�� ���� á���ϴ�.\n");
        return;
    }

    History* new_history = &history_manager->histories[history_manager->count++];

    errno_t err;
    char errBuff[100];

    err = strcpy_s(new_history->old_path, MAX_PATH_LENGTH, old_path);
    if (err) {
        strerror_s(errBuff, sizeof errBuff, err);
        fprintf(stderr, "old_path ���� �� ���� �߻�: %s\n", errBuff);
        return;
    }

    err = strcpy_s(new_history->new_path, MAX_PATH_LENGTH, new_path);
    if (err) {
        strerror_s(errBuff, sizeof errBuff, err);
        fprintf(stderr, "new_path ���� �� ���� �߻�: %s\n", errBuff);
        return;
    }

    new_history->moved_time = moved_time;
}




void print_histories(const HistoryManager* history_manager) {
    for (int i = 0; i < history_manager->count; i++) {
        History history = history_manager->histories[i];
        printf("���� [%s]��(��) [%s]�� �̵��Ǿ����ϴ�. (�ð�: %ld)\n",
            history.old_path, history.new_path, (long)history.moved_time);
    }
}

void save_history(HistoryManager* history_manager, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "���� ���⿡ �����߽��ϴ�: %s\n", filename);
        return;
    }

    for (int i = 0; i < history_manager->count; ++i) {
        History* history = &history_manager->histories[i];
        fprintf(file, "Old Path: %s, New Path: %s, Moved Time: %ld\n",
            history->old_path, history->new_path, (long)history->moved_time);
    }

    fclose(file);
}
