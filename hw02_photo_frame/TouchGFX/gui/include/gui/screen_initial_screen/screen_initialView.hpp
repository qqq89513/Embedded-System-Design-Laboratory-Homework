#ifndef SCREEN_INITIALVIEW_HPP
#define SCREEN_INITIALVIEW_HPP

#include <gui_generated/screen_initial_screen/screen_initialViewBase.hpp>
#include <gui/screen_initial_screen/screen_initialPresenter.hpp>

class screen_initialView : public screen_initialViewBase
{
public:
    screen_initialView();
    virtual ~screen_initialView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_INITIALVIEW_HPP
