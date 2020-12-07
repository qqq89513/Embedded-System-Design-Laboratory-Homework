#include <gui/screen_screen/screenView.hpp>

#include "fatfs.h"
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>     // using strlen()
#include <stdlib.h>     // using atoi()

// Globals
int bomb_cnt = 0;


// String buffer for converting
extern const uint16_t TEXTAREA_SIZE = 16;
touchgfx::Unicode::UnicodeChar buffer_bomb_cnt[TEXTAREA_SIZE];
touchgfx::Unicode::UnicodeChar buffer_debug[TEXTAREA_SIZE];
char str_bomb[TEXTAREA_SIZE];  // c-like string that will be converted to oprd1 or oprd2

// Show Unicode string or c-like string on TextArea that has one wildcard
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

screenView::screenView(){}

void screenView::setupScreen(){
  screenViewBase::setupScreen();
  
  TCHAR read_buff[64];
  FIL MyFile;
  if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 1) != FR_OK){
    printf("[Error] Failed to mount SD. @line:%d\r\n", __LINE__);
  }
  else
  {
    if(f_open(&MyFile, (TCHAR*)"sd_test.txt", FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
      printf("[Error] Failed to open file: sd_test.txt. @line:%d\r\n", __LINE__);
    else
    {
      f_printf(&MyFile, (TCHAR*)"Read/Write access to SD card is available.\n");
      f_close(&MyFile);
    }
    if(f_open(&MyFile, (TCHAR*)"sd_test.txt", FA_READ) != FR_OK)
      printf("[Error] Failed to read file: sd_test.txt. @line:%d\r\n", __LINE__);
    else
    {
      f_gets(read_buff, sizeof(read_buff), &MyFile);
      printf("%s", read_buff);
      f_close(&MyFile);
    }
  }

  // Note that printf() does nothing in touchGFX simulator
  // Use touchgfx_printf() for touchGFX simulator
  printf("TouchGFX screen_screen entered.\r\n");
  str_bomb[0] = '\0'; // Clear the string
}

void screenView::tearDownScreen(){
  screenViewBase::tearDownScreen();
}

void screenView::btn_0_onclick(){
  addCharToStr(str_bomb, '0');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_1_onclick(){
  addCharToStr(str_bomb, '1');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_2_onclick(){
  addCharToStr(str_bomb, '2');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_3_onclick(){
  addCharToStr(str_bomb, '3');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_4_onclick(){
  addCharToStr(str_bomb, '4');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_5_onclick(){
  addCharToStr(str_bomb, '5');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_6_onclick(){
  addCharToStr(str_bomb, '6');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_7_onclick(){
  addCharToStr(str_bomb, '7');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_8_onclick(){
  addCharToStr(str_bomb, '8');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_9_onclick(){
  addCharToStr(str_bomb, '9');
  showString(txt_delay_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_engage_onclick(){
  bomb_cnt = atoi(str_bomb);
  if(bomb_cnt<5)
    bomb_cnt = 5;
  else if(bomb_cnt > 99)
    bomb_cnt = 99;
}
void screenView::btn_clear_onclick(){
  str_bomb[0] = '\0';
  showString(txt_delay_cnt, buffer_bomb_cnt, "0");
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

void screenView::addCharToStr(char *str, char c){
  size_t l = strlen(str);
  if(l+1 >= TEXTAREA_SIZE){
    // Too many digits
    return;
  } 
  str[ l ] = c;
  str[ l+1 ] = '\0';
}

