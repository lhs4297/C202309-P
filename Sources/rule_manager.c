#include <stdio.h>
#include <string.h>
#include "rule_manager.h"

void init_rule_manager(RuleManager* rule_manager) {
    rule_manager->count = 0;
}

// 규칙 추가 함수
void add_rule(RuleManager* rule_manager, const char* rule_name, const char* condition) {
    // 복사
    strcpy_s(rule_manager->rules[rule_manager->count].rule_name, sizeof(rule_manager->rules[rule_manager->count].rule_name), rule_name);
    strcpy_s(rule_manager->rules[rule_manager->count].condition, sizeof(rule_manager->rules[rule_manager->count].condition), condition);
    rule_manager->count++;
}

// 규칙 삭제 함수
void delete_rule(RuleManager* rule_manager, const char* rule_name) {
    int i;

    // 규칙 관리자의 모든 규칙 검사
    for(i=0; i<rule_manager->count; i++) {
        if(strcmp(rule_manager->rules[i].rule_name, rule_name) == 0) {
            for(int j=i; j<rule_manager->count-1; j++) {
                rule_manager->rules[j] = rule_manager->rules[j+1];
            }
            rule_manager->count--;
            break;
        }
    }
}

// 업데이트 함수
void update_rule(RuleManager* rule_manager, const char* rule_name, const char* new_condition) {
    for(int i=0; i<rule_manager->count; i++) {
        // 업데이트 할 규칙과 새 규칙 이름 비교
        if(strcmp(rule_manager->rules[i].rule_name, rule_name) == 0) {
            strcpy_s(rule_manager->rules[i].condition, sizeof(rule_manager->rules[i].condition), new_condition);
            break;
        }
    }
}

void read_rules_from_file(RuleManager* rule_manager, const char* filename) {
    FILE* file;
    char rule_name[MAX_RULE_NAME];
    char condition[MAX_CONDITION];

    if (fopen_s(&file, filename, "r") != 0) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return;
    }

    while (fscanf_s(file, "%s %s", rule_name, sizeof(rule_name), condition, sizeof(condition)) != EOF) {
        add_rule(rule_manager, rule_name, condition);
    }

    fclose(file);

}
