#include <stdio.h>
#include <Windows.h>
#include <sys/stat.h>
#include "file_manager.h"
#include "rule_manager.h"

void init_file_manager(FileManager* file_manager) {
    file_manager->count = 0;
}

// 파일 목록 수집 및 정보 분석
void collect_file_info(FileManager* file_manager) {
    char target_dir[MAX_PATH_LENGTH] = "C:\\Users\\user\\Desktop\\현승\\23_1학기_학교\\C 및 PY\\C_프로젝트\\C202309-P\\Sources\\test_folder"; 

    WIN32_FIND_DATAA file_data;
    HANDLE dir_handle;

    char search_pattern[MAX_PATH_LENGTH];
    snprintf(search_pattern, sizeof(search_pattern), "%s\\*", target_dir);

    dir_handle = FindFirstFileA(search_pattern, &file_data);
    if (dir_handle == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "디렉토리를 열 수 없습니다.");   // 예외처리
        exit(1);
    }

    do {
        if (!(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char file_path[MAX_PATH_LENGTH];
            snprintf(file_path, sizeof(file_path), "%s\\%s", target_dir, file_data.cFileName);

            struct _stat file_stat;
            if (stat(file_path, &file_stat) == 0) {
                FILE* file;
                if (fopen_s(&file, file_path, "r") == 0) {
                    FileInfo file_info;
                    strcpy_s(file_info.path, sizeof(file_info.path), file_path);
                    strcpy_s(file_info.extension, sizeof(file_info.extension), strrchr(file_data.cFileName, '.') + 1);

                    // 파일 제목 읽어오기 - 보통 파일 제목은 파일 경로의 마지막 부분이므로 다음과 같이 설정할 수 있음
                    char* filename = strrchr(file_path, '\\') + 1;
                    strcpy_s(file_info.title, sizeof(file_info.title), filename);

                    file_info.created = file_stat.st_ctime;
                    file_info.size = file_stat.st_size;
                    // 파일 정보 분석 및 처리
                    file_manager->files[file_manager->count++] = file_info;
                    fclose(file);
                }
                else {
                    //실패한경우 예외처리
                    fprintf(stderr, "파일 [%s]을(를) 열 수 없습니다.\n", file_path);
                }
            }
        }
    } while (FindNextFileA(dir_handle, &file_data));

    FindClose(dir_handle);
}

void classify_and_move_files(FileManager* file_manager, RuleManager* rule_manager) {
    // 각 파일에 대하여
    for (int i = 0; i < file_manager->count; i++) {
        FileInfo file_info = file_manager->files[i];

        // RuleManager의 규칙들을 확인하여 파일을 분류
        for (int j = 0; j < rule_manager->count; j++) {
            Rule rule = rule_manager->rules[j];

            // 해당하는 규칙을 찾으면,
            if (strcmp(file_info.extension, rule.condition) == 0) {
                // 새로운 경로 생성
                char new_path[MAX_PATH_LENGTH];
                snprintf(new_path, sizeof(new_path), "%s\\%s", rule.rule_name, file_info.title);

                // 경로 존재 확인 및 생성
                if (!PathFileExists(rule.rule_name))
                    CreateDirectory(rule.rule_name, NULL);

                // 파일 이동
                if (MoveFile(file_info.path, new_path)) {
                    printf("파일 [%s]을(를) [%s]로 이동했습니다.", file_info.path, new_path);
                }
                else {
                    fprintf(stderr, "파일 [%s]을(를) 이동하지 못했습니다.", file_info.path);
                }

                break;  // 해당하는 규칙을 찾았으므로 더 이상 다른 규칙을 확인할 필요 없음
            }
        }
    }
}
