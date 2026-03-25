#ifndef HEADER_H
#define HEADER_H

/*
the HEADER structure
    TYPE:file\n
    NAME:report.pdf\n
    SIZE:204800\n
    HASH:sdhxr\n  \\for the future
    \n
    [raw bytes follow]
*/

typedef enum e_type
{
    TYPE_FILE,
    TYPE_TEXT
}t_type;

typedef struct s_header
{
    char    name[256];
    t_type  type;
    long    size;
}t_header;


int header_build(char *file, t_header *v_header); // should accespt a string (file name)

#endif
