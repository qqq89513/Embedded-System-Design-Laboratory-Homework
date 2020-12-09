#ifndef SCREEN_DISPVIEW_HPP
#define SCREEN_DISPVIEW_HPP

#include <gui_generated/screen_disp_screen/screen_dispViewBase.hpp>
#include <gui/screen_disp_screen/screen_dispPresenter.hpp>

class screen_dispView : public screen_dispViewBase
{
public:
    screen_dispView();
    virtual ~screen_dispView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    void ClickHandler(const Container &container_, const ClickEvent &e);

protected:
    uint32_t tk_show; // Previous tick to update picture
    bool paused;

    void resize_show_img(ScalableImage &img_widget, BitmapId &bmpId);

    Callback<screen_dispView, const Container &, const ClickEvent &> ClickCallback;
};

#endif // SCREEN_DISPVIEW_HPP
