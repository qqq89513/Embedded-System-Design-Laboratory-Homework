#ifndef SCREEN_GAMEVIEW_HPP
#define SCREEN_GAMEVIEW_HPP

#include <gui_generated/screen_game_screen/screen_gameViewBase.hpp>
#include <gui/screen_game_screen/screen_gamePresenter.hpp>

class screen_gameView : public screen_gameViewBase
{
public:
    screen_gameView();
    virtual ~screen_gameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

    // Declaring callback handler for Box
    void BtnHandler(const Button& Btn, const ClickEvent& Event);

    enum Grid {
      GRID_EMPTY,                 // The grid is empty and has no mine near by
      N1,N2,N3,N4,N5,N6,N7,N8,N9, // The grid has 1~9 mines near by
      GRID_MINE                   // The grid is land mine
    };

protected:
    int tickCounter;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds;
    
    touchgfx::ClickListener<touchgfx::Button>& get_btn_by_index(int8_t row, int8_t col);
    void show_btn_grid(int8_t row, int8_t col);
    void grids_clicked(Button &Btn, ClickEvent &Event);
    void show_blank_nearby(int8_t row, int8_t col);

    // Declaring callback type of box and clickEvent
    Callback<screen_gameView, const Button&, const ClickEvent&> BtnCallback;
};

#endif // SCREEN_GAMEVIEW_HPP
