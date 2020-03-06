#include <string.h>
#include <stdio.h>

char *getBrowserDir() {
    char *dest_str = "";
    strcat(dest_str, getenv("HOME"));
    strcat(dest_str, "/.browser/");
    return dest_str;
}

char *getDataBaseDir() {
    char *browser_dir = getBrowserDir();
    char *dest_str = "";
    strcat(dest_str, browser_dir);
    strcat(dest_str, "data/");
    return dest_str;
}

char *getCacheBaseDir() {
    char *browser_dir = getBrowserDir();
    char *dest_str = "";
    strcat(dest_str, browser_dir);
    strcat(dest_str, "cache/");
    return dest_str;
}