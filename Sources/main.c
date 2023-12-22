#include <stdio.h>
#include "file_manager.h"
#include "rule_manager.h"
#include "history_manager.h"

int main() {

    printf("파일 관리 시스템을 시작합니다.\n");

    // file 관리자 불러옴
    FileManager file_manager;
    init_file_manager(&file_manager);

    // 파일 목록 수집 및 정보 분석
    collect_file_info(&file_manager);

    // rule 관리자 불러옴
    RuleManager rule_manager;
    init_rule_manager(&rule_manager);

    // 파일에서 규칙 읽어오기
    read_rules_from_file(&rule_manager, "rules.txt");

    // history 관리자 불러옴
    HistoryManager history_manager;
    init_history_manager(&history_manager);


    // 파일 분류 및 이동
    classify_and_move_files(&file_manager, &rule_manager);

    // 히스토리 저장
    save_history(&history_manager, "history.txt");

    printf("파일 관리 시스템이 완료되었습니다.\n");

    return 0;
}
