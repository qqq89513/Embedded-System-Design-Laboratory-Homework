#include <gui/screen_screen/screenView.hpp>
#include <gui/common/BMPFileLoader.hpp>

#ifndef SIMULATOR
#include "fatfs.h"
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
#endif

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>     // using strlen()
#include <stdlib.h>     // using atoi()

// Globals
uint16_t delay_cnt = 0;
extern const uint16_t TEXTAREA_SIZE = 16;

#define BMP_LIST_CNT_macro 5
BitmapId bmpId[BMP_LIST_CNT_macro];
uint8_t BMP_LIST_CNT = BMP_LIST_CNT_macro; // Picture counts
const char *BMP_LIST[BMP_LIST_CNT_macro] = {"logo_1.bmp", "logo_2.bmp", "ntust_1.bmp", "ntust_2.bmp", "ntust_3.bmp"}; // bmp file list
static const uint16_t* cache = (uint16_t*)0xC003FC00;  // External SDRAM address
static const uint32_t cache_size = 1024*1024*6;        // 6MB cache

// String buffer for converting
touchgfx::Unicode::UnicodeChar buffer_delay_cnt[TEXTAREA_SIZE];
touchgfx::Unicode::UnicodeChar buffer_debug[TEXTAREA_SIZE];
char str_delay[TEXTAREA_SIZE];  // c-like string that will be converted to oprd1 or oprd2

// Show Unicode string or c-like string on TextArea that has one wildcard
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

screenView::screenView(){}

void screenView::setupScreen(){
  screenViewBase::setupScreen();
  bool SD_OK = false;   // inde
#ifndef SIMULATOR
  TCHAR read_buff[64];
  FIL MyFile;
  if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 1) != FR_OK){
    printf("[Error] Failed to mount SD. @line:%d\r\n", __LINE__);
    showString(txt_debug, buffer_debug, "No SD card");
  }
  else
  {
    if(f_open(&MyFile, (TCHAR*)"sd_test.txt", FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
      printf("[Error] Failed to open file: sd_test.txt. @line:%d\r\n", __LINE__);
    else
    {
      f_printf(&MyFile, (TCHAR*)"Read/Write access to SD card is available.\r\n");
      f_close(&MyFile);
    }
    if(f_open(&MyFile, (TCHAR*)"sd_test.txt", FA_READ) != FR_OK)
      printf("[Error] Failed to read file: sd_test.txt. @line:%d\r\n", __LINE__);
    else{
      f_gets(read_buff, sizeof(read_buff), &MyFile);
      printf("%s\r\n", read_buff);
      f_close(&MyFile);
      SD_OK = true;
    }
  }
#endif

  // Start loading BMPs to dynamic bitmaps
  if(SD_OK){
    Bitmap::removeCache();  // kill any dynamic bitmaps
    Bitmap::setCache((uint16_t*)cache, cache_size, 9);
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
    showString(txt_debug, buffer_debug, "BMP loaded");
    printf("[Info] BMP files loaded.\r\n");
  }

  // Note that printf() does nothing in touchGFX simulator
  // Use touchgfx_printf() for touchGFX simulator
  printf("TouchGFX screen_screen entered.\r\n");
  str_delay[0] = '5';
  str_delay[1] = '\0';    // Default value: "5"
}

void screenView::tearDownScreen(){
  screenViewBase::tearDownScreen();
}

void screenView::btn_0_onclick(){
  addCharToStr(str_delay, '0');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_1_onclick(){
  addCharToStr(str_delay, '1');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_2_onclick(){
  addCharToStr(str_delay, '2');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_3_onclick(){
  addCharToStr(str_delay, '3');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_4_onclick(){
  addCharToStr(str_delay, '4');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_5_onclick(){
  addCharToStr(str_delay, '5');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_6_onclick(){
  addCharToStr(str_delay, '6');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_7_onclick(){
  addCharToStr(str_delay, '7');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_8_onclick(){
  addCharToStr(str_delay, '8');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_9_onclick(){
  addCharToStr(str_delay, '9');
  showString(txt_delay_cnt, buffer_delay_cnt, str_delay);
}
void screenView::btn_engage_onclick(){
  delay_cnt = atoi(str_delay);
  if(delay_cnt<1)
    delay_cnt = 1;
  else if(delay_cnt > 99)
    delay_cnt = 99;
}
void screenView::btn_clear_onclick(){
  str_delay[0] = '\0';
  showString(txt_delay_cnt, buffer_delay_cnt, "0");
}

void screenView::addCharToStr(char *str, char c){
  size_t l = strlen(str);
  if(l+1 >= TEXTAREA_SIZE){
    // Too many digits
    return;
  } 
  str[ l ] = c;
  str[ l+1 ] = '\0';
}

// Read bmp file from SD card, create dynamic bitmap
void screenView::load_bmp(BitmapId &bmpId, const char *filename){
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

void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str){
  txtWidget.setWildcard(str);
  txtWidget.invalidate();
}
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str){
  Unicode::snprintf(buffer, TEXTAREA_SIZE, str);
  txtWidget.setWildcard(buffer);
  txtWidget.invalidate();
}
