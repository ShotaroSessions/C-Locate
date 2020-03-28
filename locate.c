/* 
    File: locate.c
    Author: Shotaro Sessions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "locate.h"

int locate(char*key, char*root)
{
    char name[260];
    DIR *directory;
    struct dirent *entry;
    int matches = 0, inner_matches;

    format_str(root);
    format_str(key);

    directory = open_dir(root);
    if(directory == NULL) {
        return -1;
    }

    while( (entry = readdir(directory)) ) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            name[0] = '\0';
            strcat(name, root);
            strcat(name, "/");
            strcat(name, entry->d_name);
            if(strstr(name, key) != NULL) {
                printf("\n%s", name);
                matches++;
            }
            if(entry->d_type == DT_DIR) {
                inner_matches = locate(key, name);
                if(inner_matches == -1) {
                    return -1;
                }
                matches += inner_matches;
            }
        }
    }
    closedir(directory);
    return matches;
}

void format_str(char * str)
{
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
        }
    }
}

DIR *open_dir(char *path)
{
    DIR *folder = opendir(path);
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return NULL;
    }
    return folder;
}
