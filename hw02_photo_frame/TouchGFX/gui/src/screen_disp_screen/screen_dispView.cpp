#include <gui/screen_disp_screen/screen_dispView.hpp>
#include <gui/common/BMPFileLoader.hpp>

#ifndef SIMULATOR
#include "fatfs.h"
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
#endif

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>     // using strlen()
#include <stdlib.h>     // using atoi()

screen_dispView::screen_dispView()
{

}

void screen_dispView::setupScreen()
{
  screen_dispViewBase::setupScreen();
  uint16_t width, height;
#ifdef SIMULATOR
  FILE* f = fopen("logo_1.bmp", "rb");
  if(f==NULL)
    touchgfx_printf("Can't open file\n");
  else
    touchgfx_printf("File opened.\n");
#else
  FIL f_obj;
  FIL* f = &f_obj;
  if(f_open(&f_obj, (TCHAR*)"logo_1.bmp", FA_READ) != FR_OK)
    printf("[Error] Failed to read file: logo_1.bmp. @line:%d\r\n", __LINE__);
  else
    printf("[Info] File opened.\r\n");
#endif
  // Get the image dimensions from the BMP file
  BMPFileLoader::getBMP24Dimensions(f, width, height);
  printf("Width:%d, Height:%d\r\n", width, height);
  BitmapId bmpId;

  // Create (16bit) dynamic bitmap of same dimension
  bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);
  if(bmpId == BITMAP_INVALID)
    printf("[Error] Failed to create dynamic bitmap. @line:%d\r\n", __LINE__);
  // Load pixels from BMP file to dynamic bitmap
  BMPFileLoader::readBMP24File(Bitmap(bmpId), f);

  // Make Image show the loaded bitmap
  img_disp.setBitmap(Bitmap(bmpId));
  img_disp.invalidate();

  printf("[Info] Screen_disp entered.\r\n");
}

void screen_dispView::tearDownScreen()
{
  screen_dispViewBase::tearDownScreen();
}
