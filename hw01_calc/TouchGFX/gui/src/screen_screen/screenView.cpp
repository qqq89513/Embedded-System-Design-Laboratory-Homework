#include <gui/screen_screen/screenView.hpp>

#include <stdio.h>      // using sprintf() for c-like string
#include <string.h>

// String buffer for converting
static const uint16_t TEXTAREA_SIZE = 32;
touchgfx::Unicode::UnicodeChar buffer_result[TEXTAREA_SIZE];
touchgfx::Unicode::UnicodeChar buffer_debug[TEXTAREA_SIZE];
static char oprd_str[TEXTAREA_SIZE];  // c-like string that will be converted to oprd1 or oprd2

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
  showString(txt_debug, btn_txt_0.getTypedText().getText());
  addCharToStr(oprd_str, '0');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_1_onclick(){
  showString(txt_debug, btn_txt_1.getTypedText().getText());
  addCharToStr(oprd_str, '1');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_2_onclick(){
  showString(txt_debug, btn_txt_2.getTypedText().getText());
  addCharToStr(oprd_str, '2');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_3_onclick(){
  showString(txt_debug, btn_txt_3.getTypedText().getText());
  addCharToStr(oprd_str, '3');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_4_onclick(){
  showString(txt_debug, btn_txt_4.getTypedText().getText());
  addCharToStr(oprd_str, '4');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_5_onclick(){
  showString(txt_debug, btn_txt_5.getTypedText().getText());
  addCharToStr(oprd_str, '5');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_6_onclick(){
  showString(txt_debug, btn_txt_6.getTypedText().getText());
  addCharToStr(oprd_str, '6');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_7_onclick(){
  showString(txt_debug, btn_txt_7.getTypedText().getText());
  addCharToStr(oprd_str, '7');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_8_onclick(){
  showString(txt_debug, btn_txt_8.getTypedText().getText());
  addCharToStr(oprd_str, '8');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_9_onclick(){
  showString(txt_debug, btn_txt_9.getTypedText().getText());
  addCharToStr(oprd_str, '9');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_00_onclick(){
  showString(txt_debug, btn_txt_00.getTypedText().getText());
  addCharToStr(oprd_str, '0');
  addCharToStr(oprd_str, '0');  // two zero
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_dot_onclick(){
  showString(txt_debug, btn_txt_dot.getTypedText().getText());
  addCharToStr(oprd_str, '.');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_plus_onclick(){
  showString(txt_debug, btn_txt_plus.getTypedText().getText());
  addCharToStr(oprd_str, '+');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_minus_onclick(){
  showString(txt_debug, btn_txt_minus.getTypedText().getText());
  addCharToStr(oprd_str, '-');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_multiply_onclick(){
  showString(txt_debug, btn_txt_multiply.getTypedText().getText());
  addCharToStr(oprd_str, '*');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_devide_onclick(){
  showString(txt_debug, btn_txt_devide.getTypedText().getText());
  addCharToStr(oprd_str, '/');
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_equal_onclick(){
  showString(txt_debug, btn_txt_equal.getTypedText().getText());

  int cnt_var = 0;          // how many varialbes converted by sscanf()
  char opr = 0;             // Operator, can be +-*/
  double oprd1=0, oprd2=0;  // Operand, can be 123.456
  double ans;               // ans = oprd1 opr oprd2

  // Extract two operands from oprd_str
  // %*[^0-9] skips every non number character: to skip +-*/
  cnt_var = sscanf(oprd_str, "%lf%*[^0-9]%lf", &oprd1, &oprd2);

  // Return if less than two of operand
  if     (cnt_var == 1) return;
  else if(cnt_var == 0){
    // No operand, there must be something messy. Clean it
    btn_clear_onclick();
    return;
  }

  // Extract the operator, it could be +-*/
  // %*f to skip the first operand.
  cnt_var = sscanf(oprd_str, "%*f%c", &opr);
  if(cnt_var == 0) return;  // No operator

  // Elementary Arithmetic
  switch(opr){
    case '+':
      ans = oprd1+oprd2;
      break;
    case '-':
      ans = oprd1-oprd2;
      break;
    case '*':
      ans = oprd1*oprd2;
      break;
    case '/':
      if(oprd2 == 0){
        showString(txt_result, buffer_result, "error");
        return;
      }
      ans = oprd1/oprd2;
      break;
    default:
      showString(txt_debug, buffer_debug, "Unknow operator.");
      return;
  }

  // Stupid feature required: On ly display the begining 10 digits
  if(ans > 1e10){
    sprintf(oprd_str, "%lf", ans);
    oprd_str[10] = '\0';
  }
  else if(ans > 1e8 || ans <= -1e8)
    sprintf(oprd_str, "%ld", (long)ans);
  else
    sprintf(oprd_str, "%.8lg", ans);

  if(strlen(oprd_str)==9){
    sprintf(oprd_str, "%.9lg", ans);
  }

  // Print the result
  showString(txt_result, buffer_result, oprd_str);
}
void screenView::btn_clear_onclick(){
  showString(txt_debug, btn_txt_clear.getTypedText().getText());
  oprd_str[0] = '\0';
  showString(txt_result, buffer_result, "0");
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

