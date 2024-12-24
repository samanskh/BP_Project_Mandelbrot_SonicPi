#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__

#include<stdlib.h>
#include<memory.h>
#include<stdio.h>

#define COLORBITS 8
#define COLORBYTES (int)(COLORBITS/8)
#define NUMCOLORS (1<<COLORBITS)

#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType; 
    unsigned int bfSize;  
    unsigned short bfReserved1; 
    unsigned short bfReserved2;  
    unsigned int bfOffBits; 
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  
    int biWidth;  
    int biHeight; 
    unsigned short biPlanes;  
    unsigned short biBitCount; 
    unsigned int biCompression; 
    unsigned int biSizeImage;  
    int biXPelsPerMeter;  
    int biYPelsPerMeter;  
    unsigned int biClrUsed;  
    unsigned int biClrImportant;  
}BITMAPINFOHEADER;

typedef struct tagCOLORTABLE {
    unsigned char b,g,r,junk;
} COLORINDEX;

typedef struct tagBitmapImageHeader {
    BITMAPFILEHEADER bmFileHeader;
    BITMAPINFOHEADER bmInfoHeader;
    COLORINDEX colorIdx[NUMCOLORS];
} BitmapImageHeader;

typedef struct tagBitMapFile {
    BitmapImageHeader bmHeader;
    unsigned char * bmData;
} BitMapFile;
#pragma pack(pop)

void InitImage(BitMapFile* pbmFile, int height, int width, int colorsUsed)
{
    unsigned int headerSize = 
        sizeof(BITMAPINFOHEADER) + 
        sizeof(BITMAPFILEHEADER) +
        sizeof(COLORINDEX) * NUMCOLORS;
        
    memset(pbmFile, 0, sizeof(BitMapFile));
    pbmFile->bmHeader.bmFileHeader.bfType =  (((unsigned short)'M') << 8) | 'B';
    pbmFile->bmHeader.bmFileHeader.bfSize = headerSize + (width * height * COLORBYTES);
    pbmFile->bmHeader.bmFileHeader.bfOffBits = headerSize;
    pbmFile->bmHeader.bmInfoHeader.biWidth = width;
    pbmFile->bmHeader.bmInfoHeader.biHeight = height;
    pbmFile->bmHeader.bmInfoHeader.biSize = 40;
    pbmFile->bmHeader.bmInfoHeader.biPlanes = 1;
    pbmFile->bmHeader.bmInfoHeader.biBitCount = COLORBITS;
    pbmFile->bmHeader.bmInfoHeader.biSizeImage = (width * height * COLORBYTES);
    pbmFile->bmHeader.bmInfoHeader.biClrImportant = colorsUsed;
    pbmFile->bmHeader.bmInfoHeader.biClrUsed = colorsUsed;
    pbmFile->bmData = (unsigned char*) malloc(width * height * COLORBYTES);
}


void WriteBitmapFile(int fileNumber, BitMapFile* pbmFile)
{
    char filename[255];
    sprintf(filename, "%05d.bmp", fileNumber);
    FILE *filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
    {
        printf("Error opening file for write.");
        return;
    }        

    fwrite(& pbmFile->bmHeader, sizeof(BitmapImageHeader), 1, filePtr);
    fwrite( pbmFile->bmData, pbmFile->bmHeader.bmInfoHeader.biSizeImage, 1, filePtr);
    fclose(filePtr);
}

#endif