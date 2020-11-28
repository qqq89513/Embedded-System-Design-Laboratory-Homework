#include <gui/screen_game_screen/screen_gameView.hpp>
#include "BitmapDatabase.hpp"
#include <stdlib.h>
#ifdef SIMULATOR
  #include <time.h>
#endif

#define ROW 8
#define COL 15
#define RANDOM(min, max) rand() % (max - min + 1) + min


// Globals
// Show Unicode string or c-like string on TextArea that has one wildcard
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, const touchgfx::Unicode::UnicodeChar *str);
extern void showString(touchgfx::TextAreaWithOneWildcard &txtWidget, touchgfx::Unicode::UnicodeChar *buffer, const char *str); // show c-like string

// String buffer for converting
extern touchgfx::Unicode::UnicodeChar buffer_bomb_cnt[];
extern touchgfx::Unicode::UnicodeChar buffer_debug[];
extern char str_bomb[];  // c-like string that will be converted to oprd1 or oprd2
extern int bomb_cnt;

// Grids datatype and table
enum Grid {
  GRID_EMPTY,                 // The grid is empty and has no mine near by
  GRID_MINE,                  // The grid is land mine
  N1,N2,N3,N4,N5,N6,N7,N8,N9  // The grid has 1~9 mines near by
};
static enum Grid table[ROW+2][COL+2] = {GRID_EMPTY};  // +2 for edge condition when placing numbers in table

screen_gameView::screen_gameView() :
  // In constructor for callback, bind to this view object and bind which function to handle the event.
  BtnCallback(this, &screen_gameView::BtnHandler) { }


void screen_gameView::setupScreen()
{
  screen_gameViewBase::setupScreen();
  showString(txt_bomb_cnt, buffer_bomb_cnt, str_bomb);

  // Fill the table with bombs
  {
    // Random seed initialize
    #ifdef SIMULATOR
      srand( time(NULL) );
    #else
      srand(0);
    #endif

    // Place bomb
    int bomb_rest = bomb_cnt; // how many bombs need to be placed in table
    while(bomb_rest>0){
      for(int8_t row=0+1; row < ROW+1; row++){
        for(int8_t col=0+1; col < COL+1; col++){
          if(bomb_rest>0 && RANDOM(0, (ROW*COL)/bomb_cnt - 1)==0 && table[row][col]!=GRID_MINE){
            bomb_rest--;
            table[row][col] = GRID_MINE;
            #ifdef SIMULATOR
            touchgfx_printf("Num.%02d mine. table[%02d][%02d] = GRID_MINE\n", bomb_cnt-bomb_rest, row, col);
            #endif
          }
        }
      }
    }
    
    // Place numbers that represent the bomb count nearby
    for(int8_t row=0+1; row < ROW+1; row++){
      for(int8_t col=0+1; col < COL+1; col++){
         if(table[row][col] != GRID_MINE){
           int8_t nearby = (table[row-1][col-1]==GRID_MINE) + (table[row-1][col]==GRID_MINE) + (table[row-1][col+1]==GRID_MINE) + \
                           (table[row  ][col-1]==GRID_MINE) +                                  (table[row  ][col+1]==GRID_MINE) + \
                           (table[row+1][col-1]==GRID_MINE) + (table[row+1][col]==GRID_MINE) + (table[row+1][col+1]==GRID_MINE) ;
            switch (nearby) {
              case 0: table[row][col] = GRID_EMPTY;  break;
              case 1: table[row][col] = N1;  break;
              case 2: table[row][col] = N2;  break;
              case 3: table[row][col] = N3;  break;
              case 4: table[row][col] = N4;  break;
              case 5: table[row][col] = N5;  break;
              case 6: table[row][col] = N6;  break;
              case 7: table[row][col] = N7;  break;
              case 8: table[row][col] = N8;  break;
              case 9: table[row][col] = N9;  break;
              
              default:;
                #ifdef SIMULATOR
                touchgfx_printf("[Error] Wrong bomb nearby count, nearby=%d. @line%d\n", nearby, __LINE__);
                #endif
            }
         }
      }
    }
  
    // Print the table when simulation
    #ifdef SIMULATOR
    touchgfx_printf("--------The tabble-----------\n");
    touchgfx_printf("X: the grid is a mine/bomb.\n");
    touchgfx_printf("1~9: the grid has 1~9 mine/bomb nearby.\n");
    touchgfx_printf("space: the grid has no mine/bomb neither has mine/bomb nearby.\n");
    touchgfx_printf("    ");
    for(int8_t col=0+1; col < COL+1; col++) touchgfx_printf("%3d", col);
    touchgfx_printf("\n    ");
    for(int8_t col=0+1; col < COL+1; col++) touchgfx_printf("___");
    touchgfx_printf("\n");
    for(int8_t row=0+1; row < ROW+1; row++){
      touchgfx_printf("%3d|", row);
      for(int8_t col=0+1; col < COL+1; col++){
        char grid_char = '\0';
        switch (table[row][col]){
          case GRID_MINE:   grid_char = 'X';    break;
          case GRID_EMPTY:  grid_char = '0';    break;
          case N1: grid_char = '1';    break;
          case N2: grid_char = '2';    break;
          case N3: grid_char = '3';    break;
          case N4: grid_char = '4';    break;
          case N5: grid_char = '5';    break;
          case N6: grid_char = '6';    break;
          case N7: grid_char = '7';    break;
          case N8: grid_char = '8';    break;
          case N9: grid_char = '9';    break;
          default:
            touchgfx_printf("[Error] table[%d][%d] not an enum. @line%d\n", row, col, __LINE__);
        }
        touchgfx_printf("  %c", grid_char);
      }
      touchgfx_printf("\n");
    }
    #endif
  }
  

  digitalHours = digiClock.getCurrentHour();
  digitalMinutes = digiClock.getCurrentMinute();
  digitalSeconds = digiClock.getCurrentSecond();

  // Buttons setAction to asscociate with BtnHandler()
  for(int8_t row=0+1; row < ROW+1; row++){
    for(int8_t col=0+1; col < COL+1; col++){
      get_btn_by_index(row, col).setClickAction(BtnCallback);
    }
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

void screen_gameView::grids_clicked(Button &Btn, ClickEvent &Event){
  // Btn.setBitmaps(touchgfx::Bitmap(BITMAP_BOMB_ID), touchgfx::Bitmap(BITMAP_CLICKED_ID));
  int8_t row = Btn.getY()/25 + 1; // row start at 1
  int8_t col = Btn.getX()/25 + 1; // col start at 1
  Button &btn_ret = get_btn_by_index(row, col);
  btn_ret.setBitmaps(touchgfx::Bitmap(BITMAP_BOMB_ID), touchgfx::Bitmap(BITMAP_CLICKED_ID));
  btn_ret.invalidate();
  #ifdef SIMULATOR
    touchgfx_printf("row:%3d, col:%3d\n", row, col);
  #endif
}

// Return a button reference corresponding to row:col
touchgfx::ClickListener<touchgfx::Button>& screen_gameView::get_btn_by_index(int8_t row, int8_t col){
  row--;  // row start at 1
  col--;  // col start at 1
  switch(row<<4 | col<<0){
    // There are total row*col=8*15=120 buttons(grids)
    // btn_row_col, from btn_0_0 to btn_3_14
    case 0x00: return btn_0_0;   case 0x10: return btn_1_0;   case 0x20: return btn_2_0;   case 0x30: return btn_3_0; 
    case 0x01: return btn_0_1;   case 0x11: return btn_1_1;   case 0x21: return btn_2_1;   case 0x31: return btn_3_1; 
    case 0x02: return btn_0_2;   case 0x12: return btn_1_2;   case 0x22: return btn_2_2;   case 0x32: return btn_3_2; 
    case 0x03: return btn_0_3;   case 0x13: return btn_1_3;   case 0x23: return btn_2_3;   case 0x33: return btn_3_3; 
    case 0x04: return btn_0_4;   case 0x14: return btn_1_4;   case 0x24: return btn_2_4;   case 0x34: return btn_3_4; 
    case 0x05: return btn_0_5;   case 0x15: return btn_1_5;   case 0x25: return btn_2_5;   case 0x35: return btn_3_5; 
    case 0x06: return btn_0_6;   case 0x16: return btn_1_6;   case 0x26: return btn_2_6;   case 0x36: return btn_3_6; 
    case 0x07: return btn_0_7;   case 0x17: return btn_1_7;   case 0x27: return btn_2_7;   case 0x37: return btn_3_7; 
    case 0x08: return btn_0_8;   case 0x18: return btn_1_8;   case 0x28: return btn_2_8;   case 0x38: return btn_3_8; 
    case 0x09: return btn_0_9;   case 0x19: return btn_1_9;   case 0x29: return btn_2_9;   case 0x39: return btn_3_9; 
    case 0x0A: return btn_0_10;  case 0x1A: return btn_1_10;  case 0x2A: return btn_2_10;  case 0x3A: return btn_3_10;
    case 0x0B: return btn_0_11;  case 0x1B: return btn_1_11;  case 0x2B: return btn_2_11;  case 0x3B: return btn_3_11;
    case 0x0C: return btn_0_12;  case 0x1C: return btn_1_12;  case 0x2C: return btn_2_12;  case 0x3C: return btn_3_12;
    case 0x0D: return btn_0_13;  case 0x1D: return btn_1_13;  case 0x2D: return btn_2_13;  case 0x3D: return btn_3_13;
    case 0x0E: return btn_0_14;  case 0x1E: return btn_1_14;  case 0x2E: return btn_2_14;  case 0x3E: return btn_3_14;

    // btn_row_col, from btn_4_0 to btn_7_14
    case 0x40: return btn_4_0;   case 0x50: return btn_5_0;   case 0x60: return btn_6_0;   case 0x70: return btn_7_0; 
    case 0x41: return btn_4_1;   case 0x51: return btn_5_1;   case 0x61: return btn_6_1;   case 0x71: return btn_7_1; 
    case 0x42: return btn_4_2;   case 0x52: return btn_5_2;   case 0x62: return btn_6_2;   case 0x72: return btn_7_2; 
    case 0x43: return btn_4_3;   case 0x53: return btn_5_3;   case 0x63: return btn_6_3;   case 0x73: return btn_7_3; 
    case 0x44: return btn_4_4;   case 0x54: return btn_5_4;   case 0x64: return btn_6_4;   case 0x74: return btn_7_4; 
    case 0x45: return btn_4_5;   case 0x55: return btn_5_5;   case 0x65: return btn_6_5;   case 0x75: return btn_7_5; 
    case 0x46: return btn_4_6;   case 0x56: return btn_5_6;   case 0x66: return btn_6_6;   case 0x76: return btn_7_6; 
    case 0x47: return btn_4_7;   case 0x57: return btn_5_7;   case 0x67: return btn_6_7;   case 0x77: return btn_7_7; 
    case 0x48: return btn_4_8;   case 0x58: return btn_5_8;   case 0x68: return btn_6_8;   case 0x78: return btn_7_8; 
    case 0x49: return btn_4_9;   case 0x59: return btn_5_9;   case 0x69: return btn_6_9;   case 0x79: return btn_7_9; 
    case 0x4A: return btn_4_10;  case 0x5A: return btn_5_10;  case 0x6A: return btn_6_10;  case 0x7A: return btn_7_10;
    case 0x4B: return btn_4_11;  case 0x5B: return btn_5_11;  case 0x6B: return btn_6_11;  case 0x7B: return btn_7_11;
    case 0x4C: return btn_4_12;  case 0x5C: return btn_5_12;  case 0x6C: return btn_6_12;  case 0x7C: return btn_7_12;
    case 0x4D: return btn_4_13;  case 0x5D: return btn_5_13;  case 0x6D: return btn_6_13;  case 0x7D: return btn_7_13;
    case 0x4E: return btn_4_14;  case 0x5E: return btn_5_14;  case 0x6E: return btn_6_14;  case 0x7E: return btn_7_14;

    default:
      #ifdef SIMULATOR
      touchgfx_printf("[Error]: row<<4|col<<0=0x%X out of range. @line:%d.\n", row<<4 | col<<0, __LINE__);
      #endif
      return btn_0_0;   // to prevent no return warning
  }
}
