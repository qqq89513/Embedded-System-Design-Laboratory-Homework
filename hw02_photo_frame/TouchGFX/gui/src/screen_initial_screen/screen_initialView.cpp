#include <gui/screen_initial_screen/screen_initialView.hpp>

extern uint32_t uwTick;

screen_initialView::screen_initialView()
{

}

void screen_initialView::setupScreen()
{
  screen_initialViewBase::setupScreen();
  tk_next_screen = uwTick;  // Update tick
}

void screen_initialView::tearDownScreen()
{
  screen_initialViewBase::tearDownScreen();
}

void screen_initialView::handleTickEvent(){
  if(uwTick-tk_next_screen > 100){
    // Go to screen after screen_initial is entered for 100ms
    application().gotoscreenScreenNoTransition();
  }
}
