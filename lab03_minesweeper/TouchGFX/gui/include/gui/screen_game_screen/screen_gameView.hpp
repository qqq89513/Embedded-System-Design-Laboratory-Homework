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

protected:
    int tickCounter;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds;
};

#endif // SCREEN_GAMEVIEW_HPP
