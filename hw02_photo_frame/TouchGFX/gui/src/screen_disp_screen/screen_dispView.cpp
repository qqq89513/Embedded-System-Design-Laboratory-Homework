#include <gui/screen_disp_screen/screen_dispView.hpp>
#include <gui/common/BMPFileLoader.hpp>

const uint16_t MAX_X = 480;  // max x (width)
const uint16_t MAX_Y = 272;  // max y (height)

extern uint16_t delay_cnt;
static const uint16_t* cache = (uint16_t*)0xC003FC00;  // External SDRAM address
static const uint32_t cache_size = 1024*1024*6;        // 6MB cache

#ifndef SIMULATOR
#include "fatfs.h"
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */

extern __IO uint32_t uwTick;  // get time tick from stm32f7xx_hal.c, increase by 1 every milli second
#endif

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>     // using strlen()
#include <stdlib.h>     // using atoi()

screen_dispView::screen_dispView():
  // In constructor for callback, bind to this view object and bind which function to handle the event.
  ClickCallback(this, &screen_dispView::ClickHandler) { }

void screen_dispView::setupScreen()
{
  screen_dispViewBase::setupScreen();
  
  Bitmap::removeCache();  // kill any dynamic bitmaps
  Bitmap::setCache((uint16_t*)cache, cache_size, 9);
  
  tk_show = uwTick;       // Update tick

  for(int i=0; i<BMP_LIST_CNT; i++){
    bmpId[i] = BITMAP_INVALID;
    load_bmp(bmpId[i], BMP_LIST[i]);
    printf("[Info] Address of BMP_LIST[%d]: %p.\r\n", i, Bitmap(bmpId[i]).getData());
    
    // Create an unused dynamic bitmap to prevent hardfault
    /* Without this line:
      Only 0,2,4 dynamic bitmaps display normally. It's not bmp file dependent.
      When display one of 1,3 bitmap, it enters hardfault.
      I think it's the bug between TouchGFX and HAL.
      The first created bitmap always displayed normally, 
      the next one is created successfully but fail to be display
      (entering hardfault, return from hardfault doesn't fix anything).
    */
    Bitmap::dynamicBitmapCreate(4, 4, Bitmap::RGB565);
  }

  paused = 0;
  container_img.setClickAction(ClickCallback);
  printf("[Info] Screen_disp entered.\r\n");
}

void screen_dispView::tearDownScreen()
{
  screen_dispViewBase::tearDownScreen();
}

// Read bmp file from SD card, create dynamic bitmap
void screen_dispView::load_bmp(BitmapId &bmpId, const char *filename){
  if(bmpId != BITMAP_INVALID){
    printf("[Error] The bitmap id should be invalid. Func:%s, Line:%d\r\n", __func__, __LINE__);
    return;
  }
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
    if(f_open(&f_obj, (TCHAR*)filename, FA_READ) != FR_OK){
      printf("[Error] Failed to read file: %s. @line:%d\r\n", filename, __LINE__);
      return;
    }
    else
      printf("[Info] File: %s opened.\r\n", filename);
  #endif

  // Get the width and height from BMP file
  uint16_t f_width, f_height;   // width and height read from file
  BMPFileLoader::getBMP24Dimensions(f, f_width, f_height);
  printf("[Info] %s: %dx%d\r\n", filename, f_width, f_height);

  // Create (16bit) dynamic bitmap of same dimension
  bmpId = Bitmap::dynamicBitmapCreate(f_width, f_height, Bitmap::RGB565);
  if(bmpId == BITMAP_INVALID){
    printf("[Error] Failed to create dynamic bitmap. @line:%d\r\n", __LINE__);
    return;
  }

  // Load pixels from BMP file to dynamic bitmap
  BMPFileLoader::readBMP24File(Bitmap(bmpId), f);
  
  // Close file
  #ifdef SIMULATOR
  fclose(f);
  #else
  f_close(f);
  #endif
}

void screen_dispView::handleTickEvent(){
  static uint8_t index = 0; // index of BMP_LIST
  if(uwTick-tk_show > delay_cnt*1000 && !paused){
    tk_show = uwTick;       // Update tick
    printf("[Info] Show BMP_LIST[%d]:%s\r\n", index, BMP_LIST[index]);
    resize_show_img(img_disp, bmpId[index]);
    if(++index >= BMP_LIST_CNT) index = 0;
  }
}

void screen_dispView::ClickHandler(const Container &container_, const ClickEvent &e){
  static uint32_t tk_paused = 0; // paused duration
  if(e.getType() == ClickEvent::RELEASED){
    paused = !paused;
    if(!paused){
      tk_show += uwTick - tk_paused;
      printf("[Info] Screen touched, slides resume.\r\n");
    }
    else{  // paused
      tk_paused = uwTick;
      printf("[Info] Screen touched, slides paused.\r\n");
    }
  }
    
}


// Set image on the widget, resize and display
void screen_dispView::resize_show_img(ScalableImage &img_widget, BitmapId &bmpId){
  if(bmpId == BITMAP_INVALID){
    printf("[Error] The bitmap id should not be invalid. Func:%s, Line:%d\r\n", __func__, __LINE__);
    return;
  }
  
  // Set bitmap to widget and resize it
  img_widget.setBitmap(Bitmap(bmpId));
  img_widget.invalidate();
  uint16_t f_width  = Bitmap(bmpId).getWidth();
  uint16_t f_height = Bitmap(bmpId).getHeight();
  uint16_t bmp_width  = f_width;
  uint16_t bmp_height = f_height;
  if(f_width > MAX_X || f_height > MAX_Y){
    bmp_width  = (f_width*MAX_Y)  / f_height;
    bmp_height = (f_height*MAX_X) / f_width;
    bmp_width  = bmp_width  < MAX_X ? bmp_width  : MAX_X;
    bmp_height = bmp_height < MAX_Y ? bmp_height : MAX_Y;
    // printf("Before resize W:%d, H:%d\r\n", f_width, f_height);
    // printf("After resize W:%d, H:%d\r\n", bmp_width, bmp_height);
  }
  img_widget.setPosition((MAX_X-bmp_width)/2, (MAX_Y-bmp_height)/2, bmp_width, bmp_height);
  img_widget.invalidate();
}
