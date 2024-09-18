#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void createGitDirectory(const char *directory) {
    char gitDirPath[256];
    snprintf(gitDirPath, sizeof(gitDirPath), "%s/.git", directory);

    struct stat st = {0};
    if (stat(gitDirPath, &st) == 0) {
        printf("Error: Directory '%s' is already a Git repository.\n", directory);
        return;
    }

    if (mkdir(gitDirPath, 0755) == -1) {
        perror("Error creating.git directory");
        return;
    }

    char configFilePath[256];
    snprintf(configFilePath, sizeof(configFilePath), "%s/.git/config", directory);
    FILE *configFile = fopen(configFilePath, "w");
    if (configFile == NULL) {
        perror("Error creating config file");
        return;
    }
    fprintf(configFile, "[core]\nrepositoryformatversion = 0\nfilemode = true\n");
    fclose(configFile);
}

int main(int argc, char *argv[]) {
    const char *directory = ".";
    if (argc > 1) {
        directory = argv[1];
    }
    createGitDirectory(directory);
    return 0;
}