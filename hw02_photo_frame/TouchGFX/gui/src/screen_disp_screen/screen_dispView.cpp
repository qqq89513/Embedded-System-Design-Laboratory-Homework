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
  FILE* f = fopen("logo_1.bmp", "rb");
  uint16_t width, height;
  if(f==NULL)
    touchgfx_printf("Can't open file\n");
  else
    touchgfx_printf("File opened.\n");

  //Get the image dimensions from the BMP file
  BMPFileLoader::getBMP24Dimensions(f, width, height);
  touchgfx_printf("Width:%d, Height:%d\n", width, height);
  BitmapId bmpId;

  //Create (16bit) dynamic bitmap of same dimension
  bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);

  //Load pixels from BMP file to dynamic bitmap
  BMPFileLoader::readBMP24File(Bitmap(bmpId), f);

  //Make Image show the loaded bitmap
  img_disp.setBitmap(Bitmap(bmpId));
  img_disp.invalidate();
}

void screen_dispView::tearDownScreen()
{
  screen_dispViewBase::tearDownScreen();
}
