#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *getBrowserDir(char *destPointer) {
    strcat(destPointer, getenv("HOME"));
    strcat(destPointer, "/.browser/");
	printf(destPointer, "\n");
	return destPointer;
}

char *getDataBaseDir(char *destPointer) {
	char browserDir[200] = "";
    getBrowserDir(browserDir);
    strcat(destPointer, browserDir);
    strcat(destPointer, "data/");
	printf(destPointer, "\n");
    return destPointer;
}

char *getCacheBaseDir(char *destPointer) {
	char browserDir[200] = "";
    getBrowserDir(browserDir);
    strcat(destPointer, browserDir);
    strcat(destPointer, "cache/");
	printf(destPointer, "\n");
    return destPointer;
}