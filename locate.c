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


    /* TODO: add format string method */
    for(int i = 0; i < strlen(root); i++) {
        if(root[i] == '\n') {
            root[i] = '\0';
        }
    }
    for(int i = 0; i < strlen(key); i++) {
        if(key[i] == '\n') {
            key[i] = '\0';
        }
    }
    /* FIXME: delete above for loops once format string method added*/


    directory = open_dir(root);
    if(directory == NULL) {
        return -1;
    }

    while( (entry = readdir(directory)) ) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..")) {
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
