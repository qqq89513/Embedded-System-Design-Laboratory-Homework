#include <gui/screen_game_screen/screen_gameView.hpp>

// Globals
// Show Unicode string or c-like string on TextArea that has one wildcard
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

// String buffer for converting
extern touchgfx::Unicode::UnicodeChar buffer_bomb_cnt[];
extern touchgfx::Unicode::UnicodeChar buffer_debug[];
extern char str_bomb[];  // c-like string that will be converted to oprd1 or oprd2
extern int bomb_cnt;

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

  btn_0_0.setClickAction(BtnCallback);
  btn_0_1.setClickAction(BtnCallback);
  btn_0_2.setClickAction(BtnCallback);
}

void screen_gameView::tearDownScreen()
{
  screen_gameViewBase::tearDownScreen();
}

void screen_gameView::BtnHandler(const Button& Btn, const ClickEvent& Event)
{
  if(&Btn == &btn_0_0){
    showString(txt_debug, buffer_debug, "0 0");
  }
  else if(&Btn == &btn_0_1){
    showString(txt_debug, buffer_debug, "0 1");
  }
  else if(&Btn == &btn_0_2){
    showString(txt_debug, buffer_debug, "0 2");
  }
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
