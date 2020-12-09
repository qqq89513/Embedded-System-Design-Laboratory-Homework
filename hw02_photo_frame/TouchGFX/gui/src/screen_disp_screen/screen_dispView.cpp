#include <gui/screen_disp_screen/screen_dispView.hpp>
#include <gui/common/BMPFileLoader.hpp>

static const uint16_t MAX_X = 480;  // max x (width)
static const uint16_t MAX_Y = 272;  // max y (height)

extern uint16_t delay_cnt;
extern uint8_t BMP_LIST_CNT; // Picture counts
extern BitmapId bmpId[];     // dynamic bit map loaded at screen(screen 1)

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
  tk_show = uwTick;       // Update tick
  paused = 0;
  container_img.setClickAction(ClickCallback);
  resize_show_img(img_disp, bmpId[0]);
  printf("[Info] Screen_disp entered.\r\n");
}

void screen_dispView::tearDownScreen()
{
  screen_dispViewBase::tearDownScreen();
}

void screen_dispView::handleTickEvent(){
  static uint8_t index = 1; // index of bmpId
  if(uwTick-tk_show > delay_cnt*1000 && !paused){
    tk_show = uwTick;       // Update tick
    printf("[Info] Show bmpId[%d]:%d\r\n", index, bmpId[index]);
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
