#ifndef SCREENVIEW_HPP
#define SCREENVIEW_HPP

#include <gui_generated/screen_screen/screenViewBase.hpp>
#include <gui/screen_screen/screenPresenter.hpp>

class screenView : public screenViewBase
{
public:
    screenView();
    virtual ~screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

protected:
    virtual void btn_0_onclick();
    virtual void btn_1_onclick();
    virtual void btn_2_onclick();
    virtual void btn_3_onclick();
    virtual void btn_4_onclick();
    virtual void btn_5_onclick();
    virtual void btn_6_onclick();
    virtual void btn_7_onclick();
    virtual void btn_8_onclick();
    virtual void btn_9_onclick();
    virtual void btn_engage_onclick();
    virtual void btn_clear_onclick();
    void addCharToStr( char *str, char c);
};

#endif // SCREENVIEW_HPP
