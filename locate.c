#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKMAX 100

char *stack[STACKMAX];
int top = -1;

void push(char* str)
{
    if(top > STACKMAX - 1) {
        perror("Stack overflow");
        exit(0);
    }
    stack[++top] = str;
}

char *pop(void)
{
    if(top < 0) {
        perror("Stack underflow");
        exit(0);
    }
    return stack[top--];
}

char * concat(char*str1, char*str2)
{
    size_t len1 = strlen(str1), len2 = strlen(str2);
    //char *concat_str = (char*) malloc(len1 + len2 + 1);
    static char concat_str[1000];
    memcpy(concat, str1, len1);
    memcpy(concat+len1, str2, len2+1);
    return concat_str;
}

char *get_path(void)
{
    static char *path = "";
    path = concat(path, stack[0]);
    for(int i = 1; i <= top; i++) {
        path = concat(path, "/");
        path = concat(path, stack[i]);
    }
    return path;
}

DIR *open_dir(char *path)
{
    DIR *folder = opendir(path);
    if(folder == NULL)
    {
        perror("Unable to read directory");
        exit(0);
    }
    return folder;
}

void recsearch(char*key, char*root)
{
    char name[260];
    DIR *directory;
    struct dirent *entry;
    directory = open_dir(root);
    while( (entry = readdir(directory)) ) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..")) {
            name[0] = '\0';
            strcat(name, root);
            strcat(name, "/");
            strcat(name, entry->d_name);
            if(strstr(name, key) != NULL) {
                printf("\n%s", name);
                //strcat(str, name);
                //strcat(str, "\n");
            }
            if(entry->d_type == DT_DIR) {
                recsearch(key, name);
            }
        }
    }
    closedir(directory);
}

void locate(char*key, char*root)
{
    //static char result[100000] = "";
    recsearch(key, root);
    //return result;
}

int main(void)
{
    
    locate("priority_planner","/home/shotaro");
}