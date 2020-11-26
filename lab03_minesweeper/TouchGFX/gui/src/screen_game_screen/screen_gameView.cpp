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

screen_gameView::screen_gameView()
{

}

void screen_gameView::setupScreen()
{
    screen_gameViewBase::setupScreen();
    showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);
}

void screen_gameView::tearDownScreen()
{
    screen_gameViewBase::tearDownScreen();
}
