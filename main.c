/* 
    File: main.c
    Author: Shotaro Sessions
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "locate.h"

int main(void)
{ 
    char key[20], root[200];
    int num_results;
    clock_t start, end;
    double time;

    printf("\n//////////////////////////////");
    printf("\n//    Locate Method Demo    //");
    printf("\n// Author: Shotaro Sessions //");
    printf("\n//////////////////////////////\n");
    printf("Enter path of directory to search in:\n");
    fgets(root, 200, stdin);
    printf("Enter key to search for:\n");
    fgets(key, 20, stdin);

    start = clock();

    num_results = locate(key, root);

    end = clock();
    time = ((double)(end - start))/CLOCKS_PER_SEC;

    if(num_results == 0) {
        printf("\nNo results found with given root: %s and key: %s\n\n", root, key);
    } else if(num_results == -1) {
        printf("\nError with given root: %s and key: %s\n\n", root, key);
    } else {
        printf("\n%d results found in %g seconds\n\n", num_results, time);
    }

}