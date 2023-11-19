#include <stdio.h>
#include <dirent.h>   // DIR, struct dirent, opendir, readdir
#include <sys/stat.h>   // struct stat, stat, S_ISREG
#include "file_manager.h"

// 파일 목록 수집 및 정보 분석
void collect_file_info(FileManager* file_manager) {
    char target_dir[MAX_PATH_LENGTH];
    printf("대상 디렉토리를 입력하세요: ");
    fgets(target_dir, sizeof(target_dir), stdin);   // 대상 디렉토리 입력 받음
    target_dir[strcspn(target_dir, "")] = '\0';   // 개행 문자 제거

    DIR* dir;
    struct dirent* entry;
    struct stat file_stat;

    dir = opendir(target_dir);   // 대상 디렉토리 열기
    if (dir == NULL) {
        fprintf(stderr, "디렉토리를 열 수 없습니다.");   // 예외처리
        exit(1);
    }

    // 반복문 : 파일들에 접근해서 파일인 경우 파일 경로 가져옴

    // 파일 경로 안에서 파일 정보 분석 ( 확장자, 생성일 등 )
    // 파일 내용읽기

    // 파일 제목 읽어옴

    //끝
}