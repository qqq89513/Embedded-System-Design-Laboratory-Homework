#include <gui/screen_screen/screenView.hpp>

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
  static int clicks=0;
  clicks++;
};
void screenView::btn_1_onclick(){};
void screenView::btn_2_onclick(){};
void screenView::btn_3_onclick(){};
void screenView::btn_4_onclick(){};
void screenView::btn_5_onclick(){};
void screenView::btn_6_onclick(){};
void screenView::btn_7_onclick(){};
void screenView::btn_8_onclick(){};
void screenView::btn_9_onclick(){};
void screenView::btn_00_onclick(){};
void screenView::btn_dot_onclick(){};
void screenView::btn_plus_onclick(){};
void screenView::btn_minus_onclick(){};
void screenView::btn_multiply_onclick(){};
void screenView::btn_devide_onclick(){};
void screenView::btn_equal_onclick(){};
void screenView::btn_clear_onclick(){};
