#include "getrows.h"
#include <unistd.h>
#include <stdio.h>

//ritorna il numero di righe dell'array passato per argomento
int getrows(char* arg) {
	FILE* fd = fopen(arg,"r");
	char scan_purpose[100]; /*!max lenght for each row = 100*/
	int rows=0;
	while(fscanf(fd,"%s",scan_purpose)!=EOF) {
		rows++;
	}
	fclose(fd);
	return rows;
}
