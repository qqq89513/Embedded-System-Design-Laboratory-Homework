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
    virtual void btn_00_onclick();
    virtual void btn_dot_onclick();
    virtual void btn_plus_onclick();
    virtual void btn_minus_onclick();
    virtual void btn_multiply_onclick();
    virtual void btn_devide_onclick();
    virtual void btn_equal_onclick();
    virtual void btn_clear_onclick();
};

#endif // SCREENVIEW_HPP
