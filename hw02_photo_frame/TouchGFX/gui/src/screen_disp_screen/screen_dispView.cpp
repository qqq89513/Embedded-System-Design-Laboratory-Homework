#include <gui/screen_disp_screen/screen_dispView.hpp>
#include <gui/common/BMPFileLoader.hpp>

const uint16_t MAX_X = 480;  // max x (width)
const uint16_t MAX_Y = 272;  // max y (height)
const char *BMP_LIST[] = {"logo_1.bmp", "logo_2.bmp", "ntust_1.bmp", "ntust_2.bmp", "ntust_3.bmp"}; // bmp file list
const uint8_t BMP_LIST_CNT = 5; // Picture counts

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
  show_bmp(img_disp, bmpId, BMP_LIST[3]);
  printf("[Info] Screen_disp entered.\r\n");
}

void screen_dispView::tearDownScreen()
{
  screen_dispViewBase::tearDownScreen();
  Bitmap::dynamicBitmapDelete(bmpId);
}

// Read bmp file from SD card, create dynamic bitmap, resize, and display
void screen_dispView::show_bmp(ScalableImage &img_widget, BitmapId &bmpId, const char *filename){

  // Open file
  #ifdef SIMULATOR
    FILE* f = fopen(filename, "rb");
    if(f==NULL)
      touchgfx_printf("Can't open file: %s\n", filename);
    else
      touchgfx_printf("File opened.\n");
  #else  // HAL
    FIL f_obj;
    FIL* f = &f_obj;
    if(f_open(&f_obj, (TCHAR*)filename, FA_READ) != FR_OK)
      printf("[Error] Failed to read file: %s. @line:%d\r\n", filename, __LINE__);
    else
      printf("[Info] File opened.\r\n");
  #endif

  // Get the width and height from BMP file
  uint16_t f_width, f_height;   // width and height read from file
  BMPFileLoader::getBMP24Dimensions(f, f_width, f_height);
  printf("[Info] %s: %dx%d\r\n", filename, f_width, f_height);

  // Create (16bit) dynamic bitmap of same dimension
  bmpId = Bitmap::dynamicBitmapCreate(f_width, f_height, Bitmap::RGB565);
  if(bmpId == BITMAP_INVALID)
    printf("[Error] Failed to create dynamic bitmap. @line:%d\r\n", __LINE__);

  // Load pixels from BMP file to dynamic bitmap
  BMPFileLoader::readBMP24File(Bitmap(bmpId), f);

  // Set bitmap to widget and resize it
  img_widget.setBitmap(Bitmap(bmpId));
  uint16_t bmp_width  = f_width;
  uint16_t bmp_height = f_height;
  if(f_width > MAX_X || f_height > MAX_Y){
    bmp_width  = (f_width*MAX_Y)  / f_height;
    bmp_height = (f_height*MAX_X) / f_width;
    bmp_width  = bmp_width  < MAX_X ? bmp_width  : MAX_X;
    bmp_height = bmp_height < MAX_Y ? bmp_height : MAX_Y;
    printf("Before resize W:%d, H:%d\n", f_width, f_height);
    printf("After resize W:%d, H:%d\n", bmp_width, bmp_height);
  }
  img_widget.setPosition((MAX_X-bmp_width)/2, (MAX_Y-bmp_height)/2, bmp_width, bmp_height);
  img_widget.invalidate();
}
