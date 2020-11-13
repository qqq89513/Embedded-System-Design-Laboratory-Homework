#include <gui/screen_screen/screenView.hpp>

static const uint16_t TEXTAREA_SIZE = 16;
touchgfx::Unicode::UnicodeChar textAreaBuffer[TEXTAREA_SIZE];

// Show Unicode string or c-like string on TextArea that has one wildcard
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const char *str);  // c-like string

screenView::screenView()
{

}

void screenView::setupScreen()
{
    screenViewBase::setupScreen();
}

void screenView::tearDownScreen()
{
    screenViewBase::tearDownScreen();
}

void screenView::btn_0_onclick(){
  showString(txt_debug, btn_txt_0.getTypedText().getText());
}
void screenView::btn_1_onclick(){
  showString(txt_debug, btn_txt_1.getTypedText().getText());
}
void screenView::btn_2_onclick(){
  showString(txt_debug, btn_txt_2.getTypedText().getText());
}
void screenView::btn_3_onclick(){
  showString(txt_debug, btn_txt_3.getTypedText().getText());
}
void screenView::btn_4_onclick(){
  showString(txt_debug, btn_txt_4.getTypedText().getText());
}
void screenView::btn_5_onclick(){
  showString(txt_debug, btn_txt_5.getTypedText().getText());
}
void screenView::btn_6_onclick(){
  showString(txt_debug, btn_txt_6.getTypedText().getText());
}
void screenView::btn_7_onclick(){
  showString(txt_debug, btn_txt_7.getTypedText().getText());
}
void screenView::btn_8_onclick(){
  showString(txt_debug, btn_txt_8.getTypedText().getText());
}
void screenView::btn_9_onclick(){
  showString(txt_debug, btn_txt_9.getTypedText().getText());
}
void screenView::btn_00_onclick(){
  showString(txt_debug, btn_txt_00.getTypedText().getText());
}
void screenView::btn_dot_onclick(){
  showString(txt_debug, btn_txt_dot.getTypedText().getText());
}
void screenView::btn_plus_onclick(){
  showString(txt_debug, btn_txt_plus.getTypedText().getText());
}
void screenView::btn_minus_onclick(){
  showString(txt_debug, btn_txt_minus.getTypedText().getText());
}
void screenView::btn_multiply_onclick(){
  showString(txt_debug, btn_txt_multiply.getTypedText().getText());
}
void screenView::btn_devide_onclick(){
  showString(txt_debug, btn_txt_devide.getTypedText().getText());
}
void screenView::btn_equal_onclick(){
  showString(txt_debug, btn_txt_equal.getTypedText().getText());
}
void screenView::btn_clear_onclick(){
  showString(txt_debug, btn_txt_clear.getTypedText().getText());
  showString(txt_result, "");
}

void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str){
  txtWidget.setWildcard(str);
  txtWidget.invalidate();
}

void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const char *str){
  Unicode::snprintf(textAreaBuffer, TEXTAREA_SIZE, str);
  txtWidget.setWildcard(textAreaBuffer);
  txtWidget.invalidate();
}
