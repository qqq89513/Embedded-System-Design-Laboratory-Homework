#include <gui/screen_screen/screenView.hpp>

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>     // using strlen()
#include <stdlib.h>     // using atoi()

// Globals
int bomb_cnt = 0;


// String buffer for converting
const uint16_t TEXTAREA_SIZE = 16;
touchgfx::Unicode::UnicodeChar buffer_bomb_cnt[TEXTAREA_SIZE];
touchgfx::Unicode::UnicodeChar buffer_debug[TEXTAREA_SIZE];
char str_bomb[TEXTAREA_SIZE];  // c-like string that will be converted to oprd1 or oprd2

// Show Unicode string or c-like string on TextArea that has one wildcard
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

screenView::screenView(){}

void screenView::setupScreen(){
  screenViewBase::setupScreen();
}

void screenView::tearDownScreen(){
  screenViewBase::tearDownScreen();
}

void screenView::btn_0_onclick(){
  showString(txt_debug, txt_0.getTypedText().getText());
  addCharToStr(str_bomb, '0');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_1_onclick(){
  showString(txt_debug, txt_1.getTypedText().getText());
  addCharToStr(str_bomb, '1');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_2_onclick(){
  showString(txt_debug, txt_2.getTypedText().getText());
  addCharToStr(str_bomb, '2');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_3_onclick(){
  showString(txt_debug, txt_3.getTypedText().getText());
  addCharToStr(str_bomb, '3');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_4_onclick(){
  showString(txt_debug, txt_4.getTypedText().getText());
  addCharToStr(str_bomb, '4');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_5_onclick(){
  showString(txt_debug, txt_5.getTypedText().getText());
  addCharToStr(str_bomb, '5');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_6_onclick(){
  showString(txt_debug, txt_6.getTypedText().getText());
  addCharToStr(str_bomb, '6');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_7_onclick(){
  showString(txt_debug, txt_7.getTypedText().getText());
  addCharToStr(str_bomb, '7');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_8_onclick(){
  showString(txt_debug, txt_8.getTypedText().getText());
  addCharToStr(str_bomb, '8');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_9_onclick(){
  showString(txt_debug, txt_9.getTypedText().getText());
  addCharToStr(str_bomb, '9');
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}
void screenView::btn_engage_onclick(){
  bomb_cnt = atoi(str_bomb);
}
void screenView::btn_clear_onclick(){
  showString(txt_debug, txt_c.getTypedText().getText());
  str_bomb[0] = '\0';
  showString(txt_bomb_cnt, buffer_bomb_cnt, "0");
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
    showString(txt_debug, buffer_debug, "Too many digits.");
    return;
  } 
  str[ l ] = c;
  str[ l+1 ] = '\0';
}

