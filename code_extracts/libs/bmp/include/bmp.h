/* 
* bmp.h
*/

#ifndef BMP_H
#define BMP_H

#include "libft.h"

#include <stdlib.h>
#include <fcntl.h> //open
#include <unistd.h> //read

#define MAINHEADERSIZE 14

#define BITMAPCOREHEADER 12
#define BITMAPINFOHEADER 40

typedef enum      i_textureType
{
    BI_RGB = 0x1907,
    BI_BITFIELDS = 0x1908
}                  e_textureType;

#pragma pack(push, 1)

typedef struct		s_mainheader
{
    char name[2];
    unsigned int size;
    unsigned int reserved;
    unsigned int offset;
}					t_mainheader;

typedef struct		s_coreheader
{
    short width;
    unsigned int size;
    short height;
    short colorPlanes;
    short depth;
}					t_coreheader;

typedef struct		s_infoheader
{
    unsigned int size;
    int width;
    int height;
    short colorPlanes;
    short depth;
    int compression;
    int rawSize;
    int hRes;
    int vRes;
    int colorPalette;
    int importantColor;
}					t_infoheader;

#pragma pack(pop)

typedef struct		s_texture
{
    int width;
    int height;
    e_textureType type;
    unsigned char *bytes;
}					t_texture;

t_texture* BMPread(char *name);

#endif