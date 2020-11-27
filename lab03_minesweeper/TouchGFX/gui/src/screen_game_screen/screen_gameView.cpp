#include <gui/screen_game_screen/screen_gameView.hpp>
#include "BitmapDatabase.hpp"

// Globals
// Show Unicode string or c-like string on TextArea that has one wildcard
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

// String buffer for converting
extern touchgfx::Unicode::UnicodeChar buffer_bomb_cnt[];
extern touchgfx::Unicode::UnicodeChar buffer_debug[];
extern char str_bomb[];  // c-like string that will be converted to oprd1 or oprd2
extern int bomb_cnt;


void grids_clicked(Button &Btn, ClickEvent &Event);

screen_gameView::screen_gameView() :
  // In constructor for callback, bind to this view object and bind which function to handle the event.
  BtnCallback(this, &screen_gameView::BtnHandler) { }


void screen_gameView::setupScreen()
{
  screen_gameViewBase::setupScreen();
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
  digitalHours = digiClock.getCurrentHour();
  digitalMinutes = digiClock.getCurrentMinute();
  digitalSeconds = digiClock.getCurrentSecond();

  // Buttons setAction to asscociate with BtnHandler()
  {
    // There are total row*col=8*15=120 buttons(grids)
    // btn_row_col, from btn_0_0 to btn_3_14
    btn_0_0.setClickAction(BtnCallback);   btn_1_0.setClickAction(BtnCallback);   btn_2_0.setClickAction(BtnCallback);   btn_3_0.setClickAction(BtnCallback); 
    btn_0_1.setClickAction(BtnCallback);   btn_1_1.setClickAction(BtnCallback);   btn_2_1.setClickAction(BtnCallback);   btn_3_1.setClickAction(BtnCallback); 
    btn_0_2.setClickAction(BtnCallback);   btn_1_2.setClickAction(BtnCallback);   btn_2_2.setClickAction(BtnCallback);   btn_3_2.setClickAction(BtnCallback); 
    btn_0_3.setClickAction(BtnCallback);   btn_1_3.setClickAction(BtnCallback);   btn_2_3.setClickAction(BtnCallback);   btn_3_3.setClickAction(BtnCallback); 
    btn_0_4.setClickAction(BtnCallback);   btn_1_4.setClickAction(BtnCallback);   btn_2_4.setClickAction(BtnCallback);   btn_3_4.setClickAction(BtnCallback); 
    btn_0_5.setClickAction(BtnCallback);   btn_1_5.setClickAction(BtnCallback);   btn_2_5.setClickAction(BtnCallback);   btn_3_5.setClickAction(BtnCallback); 
    btn_0_6.setClickAction(BtnCallback);   btn_1_6.setClickAction(BtnCallback);   btn_2_6.setClickAction(BtnCallback);   btn_3_6.setClickAction(BtnCallback); 
    btn_0_7.setClickAction(BtnCallback);   btn_1_7.setClickAction(BtnCallback);   btn_2_7.setClickAction(BtnCallback);   btn_3_7.setClickAction(BtnCallback); 
    btn_0_8.setClickAction(BtnCallback);   btn_1_8.setClickAction(BtnCallback);   btn_2_8.setClickAction(BtnCallback);   btn_3_8.setClickAction(BtnCallback); 
    btn_0_9.setClickAction(BtnCallback);   btn_1_9.setClickAction(BtnCallback);   btn_2_9.setClickAction(BtnCallback);   btn_3_9.setClickAction(BtnCallback); 
    btn_0_10.setClickAction(BtnCallback);  btn_1_10.setClickAction(BtnCallback);  btn_2_10.setClickAction(BtnCallback);  btn_3_10.setClickAction(BtnCallback);
    btn_0_11.setClickAction(BtnCallback);  btn_1_11.setClickAction(BtnCallback);  btn_2_11.setClickAction(BtnCallback);  btn_3_11.setClickAction(BtnCallback);
    btn_0_12.setClickAction(BtnCallback);  btn_1_12.setClickAction(BtnCallback);  btn_2_12.setClickAction(BtnCallback);  btn_3_12.setClickAction(BtnCallback);
    btn_0_13.setClickAction(BtnCallback);  btn_1_13.setClickAction(BtnCallback);  btn_2_13.setClickAction(BtnCallback);  btn_3_13.setClickAction(BtnCallback);
    btn_0_14.setClickAction(BtnCallback);  btn_1_14.setClickAction(BtnCallback);  btn_2_14.setClickAction(BtnCallback);  btn_3_14.setClickAction(BtnCallback);

    // btn_row_col, from btn_4_0 to btn_7_14
    btn_4_0.setClickAction(BtnCallback);   btn_5_0.setClickAction(BtnCallback);   btn_6_0.setClickAction(BtnCallback);   btn_7_0.setClickAction(BtnCallback); 
    btn_4_1.setClickAction(BtnCallback);   btn_5_1.setClickAction(BtnCallback);   btn_6_1.setClickAction(BtnCallback);   btn_7_1.setClickAction(BtnCallback); 
    btn_4_2.setClickAction(BtnCallback);   btn_5_2.setClickAction(BtnCallback);   btn_6_2.setClickAction(BtnCallback);   btn_7_2.setClickAction(BtnCallback); 
    btn_4_3.setClickAction(BtnCallback);   btn_5_3.setClickAction(BtnCallback);   btn_6_3.setClickAction(BtnCallback);   btn_7_3.setClickAction(BtnCallback); 
    btn_4_4.setClickAction(BtnCallback);   btn_5_4.setClickAction(BtnCallback);   btn_6_4.setClickAction(BtnCallback);   btn_7_4.setClickAction(BtnCallback); 
    btn_4_5.setClickAction(BtnCallback);   btn_5_5.setClickAction(BtnCallback);   btn_6_5.setClickAction(BtnCallback);   btn_7_5.setClickAction(BtnCallback); 
    btn_4_6.setClickAction(BtnCallback);   btn_5_6.setClickAction(BtnCallback);   btn_6_6.setClickAction(BtnCallback);   btn_7_6.setClickAction(BtnCallback); 
    btn_4_7.setClickAction(BtnCallback);   btn_5_7.setClickAction(BtnCallback);   btn_6_7.setClickAction(BtnCallback);   btn_7_7.setClickAction(BtnCallback); 
    btn_4_8.setClickAction(BtnCallback);   btn_5_8.setClickAction(BtnCallback);   btn_6_8.setClickAction(BtnCallback);   btn_7_8.setClickAction(BtnCallback); 
    btn_4_9.setClickAction(BtnCallback);   btn_5_9.setClickAction(BtnCallback);   btn_6_9.setClickAction(BtnCallback);   btn_7_9.setClickAction(BtnCallback); 
    btn_4_10.setClickAction(BtnCallback);  btn_5_10.setClickAction(BtnCallback);  btn_6_10.setClickAction(BtnCallback);  btn_7_10.setClickAction(BtnCallback);
    btn_4_11.setClickAction(BtnCallback);  btn_5_11.setClickAction(BtnCallback);  btn_6_11.setClickAction(BtnCallback);  btn_7_11.setClickAction(BtnCallback);
    btn_4_12.setClickAction(BtnCallback);  btn_5_12.setClickAction(BtnCallback);  btn_6_12.setClickAction(BtnCallback);  btn_7_12.setClickAction(BtnCallback);
    btn_4_13.setClickAction(BtnCallback);  btn_5_13.setClickAction(BtnCallback);  btn_6_13.setClickAction(BtnCallback);  btn_7_13.setClickAction(BtnCallback);
    btn_4_14.setClickAction(BtnCallback);  btn_5_14.setClickAction(BtnCallback);  btn_6_14.setClickAction(BtnCallback);  btn_7_14.setClickAction(BtnCallback);
  }
}

void screen_gameView::tearDownScreen()
{
  screen_gameViewBase::tearDownScreen();
}

void screen_gameView::BtnHandler(const Button& Btn, const ClickEvent& Event)
{
  if(Event.getType() == Event.RELEASED)
    grids_clicked(const_cast <Button&>(Btn), const_cast <ClickEvent&>(Event));
}

void screen_gameView::handleTickEvent(){
  tickCounter++;

  if (tickCounter % 60 == 0){
    if (++digitalSeconds >= 60){
      digitalSeconds = 0;
      if (++digitalMinutes >= 60){
        digitalMinutes = 0;
        if (++digitalHours >= 24)
          digitalHours = 0;
      }
    }
    // Update the clock
    // In UI, Second is set to invisible. So display hr:min:sec as digitalMinutes:digitalSeconds
    digiClock.setTime24Hour(digitalMinutes, digitalSeconds, 0);
  }
}

void grids_clicked(Button &Btn, ClickEvent &Event){
  // Btn.setBitmaps(touchgfx::Bitmap(BITMAP_BOMB_ID), touchgfx::Bitmap(BITMAP_CLICKED_ID));
  int8_t row = Btn.getY()/25;
  int8_t col = Btn.getX()/25;

  #ifdef SIMULATOR
    touchgfx_printf("row:%3d, col:%3d\n", row, col);
  #endif


  Btn.invalidate();
}


