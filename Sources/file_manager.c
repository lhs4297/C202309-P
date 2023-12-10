#include <stdio.h>
#include <Windows.h>
#include <sys/stat.h>
#include "file_manager.h"

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

            struct stat file_stat;
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
                    fclose(file);
                }
            }
        }
    } while (FindNextFileA(dir_handle, &file_data));

    FindClose(dir_handle);
}


/*
void collect_file_info(FileManager* file_manager) {
    char target_dir[MAX_PATH_LENGTH];

    printf("대상 디렉토리를 입력하세요: ");
    fgets(target_dir, sizeof(target_dir), stdin);   // 대상 디렉토리 입력 받음
    target_dir[strcspn(target_dir, "\n")] = '\0';   // 개행 문자 제거

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

            struct stat file_stat;
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
                    fclose(file);
                }
            }
        }
    } while (FindNextFileA(dir_handle, &file_data));

    FindClose(dir_handle);



    // 파일 경로 안에서 파일 정보 분석 ( 확장자, 생성일 등 )
    // 파일 내용 읽기 ( 불가 삭제 예정, 텍스트파일 또는 csv파일만 읽을 수 있기 때문 )
    // 파일 제목 읽어오기 ( 불가 삭제 예정 )

    // 끝
}
*/
