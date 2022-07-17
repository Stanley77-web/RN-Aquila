#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "List.h"

#define FILE_SIZE 4096
#define BUFFER_SIZE 512
#define BLOCK 256

List ListDir(const char * path);
int SearchFile (const char * text, const char * pattern, int length);
void PrintDirFile (int fd);

int main(int argc, char ** args) {
    char * filename;
    char buffer[FILE_SIZE];    
    
    double start_time, end_time;
    DIR * dir;
    
    Addr P;
    List L;
    FileDes file_desc;

    if (argc < 4) {
        printf("Not enough variable.\n");
        printf("Run Program: ./paringder nProcess nThread pattern_string\n");
        exit(0);
    }

    int nProcess, nTheard;
    char * pattern;

    nProcess = atoi(args[1]);
    nTheard = atoi(args[2]);
    pattern = args[3];

    L = ListDir(".");
    
    start_time = omp_get_wtime();

    P = L;

    int cchild = 0;

    pid_t child_id;
    int status;

    int count;

    while (P != NULL) {
        if ((child_id = fork()) == 0) {
            goto child_process;
        }

        cchild++;
        if (cchild == nProcess) {
            child_id = wait(&status);
            cchild--;
        }
        P = P->next;
    }

    while (cchild > 0) {
        child_id = wait(&status);
        cchild--;
    }

    end_time = omp_get_wtime();

    printf("Total compile time %f second(s).\n", end_time-start_time);
    exit(0);
    
    child_process:
        file_desc = P->info;

        FILE * fs = fdopen(file_desc, "rb");
        fread(buffer, 1, FILE_SIZE, fs);

        int i = 0;
        int found = 0;

        omp_set_num_threads(nTheard);
        while (buffer[i] != '\0' && !found) {
            if (SearchFile(&buffer[i], pattern, BLOCK)) {
                PrintDirFile(file_desc);
                found = 1;
            }
            i += BLOCK;
        }
    return 0;
}

List ListDir(const char * path) {
    Addr P;
    List L;
    DIR * dir;
    struct dirent * dirent;
    char dir_path[BUFFER_SIZE];

    L = NULL;
    dir = opendir(path);

    if (dir == NULL) return NULL;

    P = Allocation(0);

    while ((dirent = readdir(dir)) != NULL) {
        sprintf(dir_path, "%s/%s", path, dirent->d_name);

        if (dirent->d_type != DT_DIR) {
            P->next = Allocation(fileno(fopen(dir_path, "r")));
            P = P->next;
            if (L == NULL) L = P;
        }
        else if (dirent->d_type == DT_DIR 
                 && !strcmp(dirent->d_name, "..") 
                 && !strcmp(dirent->d_name, ".")) {
            P->next = ListDir(dir_path);

            if (P->next != NULL) {
                LastNode(P->next, &P);
                if (L == NULL) L = P;
            }
        }
    }
    closedir(dir);
    return L;
}

int SearchFile (const char * text, const char * pattern, int length) {
    size_t count;

    for (int i = 0; i < length; i++) {
        count = 0;
        for (int j = 0; pattern[j] != '\0' &&
                        text[i+j] != '\0';
                 j++) {
                count++;
                if (text[i+j] != pattern[j]) break;
        }
        if (count == strlen(pattern)) return 1;
    }
    return 0;
}

void PrintDirFile (int fd) {
    char path_file[BLOCK], buffer[BLOCK];

    sprintf(path_file, "/proc/self/fd/%d", fd);
    memset(buffer, 0, sizeof(buffer));
    readlink(path_file, buffer, sizeof(buffer));
    printf("Pattern dicover at %s\n", buffer);
} 