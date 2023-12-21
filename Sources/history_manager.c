#include <stdio.h>
#include "history_manager.h"



void print_histories(const /*히스토리*/ * history_manager) {
    for (int i = 0; i < history_manager->count; i++) {
        /*히스토리*/ history = history_manager->histories[i];
        printf("파일 [%s]이(가) [%s]로 이동되었습니다. (시간: %ld)\n",
            history.old_path, history.new_path, history.moved_time);
    }