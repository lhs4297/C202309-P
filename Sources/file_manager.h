#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#define MAX_FILES 100   // 파일 최대 개수
#define MAX_PATH_LENGTH 1024   // 파일 경로의 최대 길이
#define MAX_CONTENT_LENGTH 1024   // 파일 내용 최대 길이

typedef struct {   // 파일 내용 저장하기 위해 필요한 곳
    char path[MAX_PATH_LENGTH];
    char extension[10];
    time_t created;
    long size;
    char content[MAX_CONTENT_LENGTH];
    char title[MAX_PATH_LENGTH];
} FileInfo;

typedef struct {   // FileInfo 구조체 배열과 파일 개수를 저장하기 위한 멤버로 구성
    FileInfo files[MAX_FILES];
    int count;
} FileManager;


// 함수들 초기화, 파일 정보 수집
void init_file_manager(FileManager* file_manager);
void collect_file_info(FileManager* file_manager);
void classify_and_move_files(FileManager* file_manager, RuleManager* rule_manager);

#endif
