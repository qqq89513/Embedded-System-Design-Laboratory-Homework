#include <gui/screen_screen/screenView.hpp>

// show TypedText on specific text widget
void showText(touchgfx::TextArea &txtWidget, TypedText txt);

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
  showText(txt_debug, btn_txt_0.getTypedText());
}
void screenView::btn_1_onclick(){
  showText(txt_debug, btn_txt_1.getTypedText());
}
void screenView::btn_2_onclick(){
  showText(txt_debug, btn_txt_2.getTypedText());
}
void screenView::btn_3_onclick(){
  showText(txt_debug, btn_txt_3.getTypedText());
}
void screenView::btn_4_onclick(){
  showText(txt_debug, btn_txt_4.getTypedText());
}
void screenView::btn_5_onclick(){
  showText(txt_debug, btn_txt_5.getTypedText());
}
void screenView::btn_6_onclick(){
  showText(txt_debug, btn_txt_6.getTypedText());
}
void screenView::btn_7_onclick(){
  showText(txt_debug, btn_txt_7.getTypedText());
}
void screenView::btn_8_onclick(){
  showText(txt_debug, btn_txt_8.getTypedText());
}
void screenView::btn_9_onclick(){
  showText(txt_debug, btn_txt_9.getTypedText());
}
void screenView::btn_00_onclick(){
  showText(txt_debug, btn_txt_00.getTypedText());
}
void screenView::btn_dot_onclick(){
  showText(txt_debug, btn_txt_dot.getTypedText());
}
void screenView::btn_plus_onclick(){
  showText(txt_debug, btn_txt_plus.getTypedText());
}
void screenView::btn_minus_onclick(){
  showText(txt_debug, btn_txt_minus.getTypedText());
}
void screenView::btn_multiply_onclick(){
  showText(txt_debug, btn_txt_multiply.getTypedText());
}
void screenView::btn_devide_onclick(){
  showText(txt_debug, btn_txt_devide.getTypedText());
}
void screenView::btn_equal_onclick(){
  showText(txt_debug, btn_txt_equal.getTypedText());
}
void screenView::btn_clear_onclick(){
  showText(txt_debug, btn_txt_clear.getTypedText());
}

// show TypedText on specific text widget
void showText(touchgfx::TextArea &txtWidget, TypedText txt){
  txtWidget.setTypedText(txt);
  txtWidget.invalidate();
  txtWidget.resizeToCurrentText();
  txtWidget.invalidate();
}
