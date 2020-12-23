#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Bitmap.hpp>

#ifndef SIMULATOR
#include "fatfs.h"
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
#else
#include <stdio.h>
#endif

using namespace touchgfx;

class BMPFileLoader
{
public:
#ifdef SIMULATOR
    typedef void* FileHdl;
#else
    typedef FIL* FileHdl;
#endif

    static void getBMP24Dimensions(FileHdl fileHandle, uint16_t& width, uint16_t& height);
    static void readBMP24File(Bitmap bitmap, FileHdl fileHandle);
private:
    static int readFile(FileHdl hdl, uint8_t* const buffer, uint32_t length);
    static void seekFile(FileHdl hdl, uint32_t offset);
};