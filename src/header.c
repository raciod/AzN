#include "../include/header.h"
#include <string.h>
/*
the HEADER structure
    TYPE:file\n
    NAME:report.pdf\n
    SIZE:204800\n
    HASH:sdhxr\n  \\for the future
    \n
    [raw bytes follow]
*/

int header_build(char *file, t_header *v_header){
    strncpy(v_header->name, file, sizeof(v_header->name) - 1);
    v_header->name[sizeof(v_header->name) - 1] = '\0';
    v_header->type = TYPE_FILE;
    v_header->size = 10000;

    return 0;
}

// write the read function

// unsigned char   *read_file(char *path, long *size)
// {
//     FILE            *fd;
//     unsigned char   *buffer;
//
//     fd = fopen(path, "rb");
//     if(!fd)
//         return NULL;
//     fseek(fd, 0, SEEK_END);
//     *size = ftell(fd);
//     fseek(fd, 0, SEEK_SET);
//     buffer = malloc(*size);
//     if(!buffer)
//     {
//         fclose(fd);
//         return NULL;
//     }
//     fread(buffer, 1, *size, fd);
//     fclose(fd);
//     return buffer;
// }
