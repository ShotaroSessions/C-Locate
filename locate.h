/* 
    File: locate.h
    Author: Shotaro Sessions
*/

#ifndef LOCATE_H
#define LOCATE_H

#include <dirent.h>

/*
    Locate method, prints paths of all files with param 'key' within
    their name/path in directory with the name/path in param 'root'
*/
int locate(char*key, char*root);

/*
    Opens directory and returns a DIR pointer.
    Prints an error if failure.
*/
DIR *open_dir(char *path);

#endif