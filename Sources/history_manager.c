#include <stdio.h>
#include "history_manager.h"



void print_histories(const /*�����丮*/ * history_manager) {
    for (int i = 0; i < history_manager->count; i++) {
        /*�����丮*/ history = history_manager->histories[i];
        printf("���� [%s]��(��) [%s]�� �̵��Ǿ����ϴ�. (�ð�: %ld)\n",
            history.old_path, history.new_path, history.moved_time);
    }