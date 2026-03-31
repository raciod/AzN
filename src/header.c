#include "../include/header.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
the HEADER structure
    TYPE:file\n
    NAME:report.pdf\n
    SIZE:204800\n
    HASH:sdhxr\n  \\for the future
    \n
    [raw bytes follow]
*/

int header_build(char *file, t_header *v_header, FILE *fptr){

    strncpy(v_header->name, file, sizeof(v_header->name) - 1);
    v_header->name[sizeof(v_header->name) - 1] = '\0';

    strncpy(v_header->type, "TYPE_FILE", sizeof(v_header->type) - 1);
    v_header->type[sizeof(v_header->type) - 1] = '\0';
    

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    v_header->size = size;

    return 0;
}

int header_parse(char *header, t_header *v_header){  
    // %32[^ \n] means: read up to 32 characters, stopping at a space or newline
    // %ld means: read a long integer
    int fields = sscanf(header, 
                        "TYPE:%32[^\n]\nNAME:%255[^\n]\nSIZE:%ld", 
                        v_header->type, 
                        v_header->name, 
                        &v_header->size);

    if (fields != 3) {
        return 1; // Error
    }

    return 0;
}

