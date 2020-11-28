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

protected:
    int tickCounter;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds;
    
    touchgfx::ClickListener<touchgfx::Button>& get_btn_by_index(int8_t row, int8_t col);
    void show_btn_grid(int8_t row, int8_t col);
    void grids_clicked(Button &Btn, ClickEvent &Event);

    // Declaring callback type of box and clickEvent
    Callback<screen_gameView, const Button&, const ClickEvent&> BtnCallback;
};

#endif // SCREEN_GAMEVIEW_HPP
