#include "search.h"
#include <string.h>
#include <stdio.h>


//ricerca diretta della stringa target nella matrice data
void search(char data[][100], int rows, char* target, int start, int limit, int fd, int numTrovati) {
    if (fd>=0) {
        dup2(fd,1);
    }

    while (start<rows && limit>=0) {
        if (strcmp(data[start],target)==0) {
            limit--;
            numTrovati++;
            printf("%d\n",start+1);
        }
        start++;
    }
    if (numTrovati==0) {
        printf("0\n");
    }
}
