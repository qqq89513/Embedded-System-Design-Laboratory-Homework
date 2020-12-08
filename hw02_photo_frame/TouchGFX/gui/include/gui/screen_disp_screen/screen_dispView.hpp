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

protected:
    uint32_t tk_show; // Previous tick to update picture
    uint32_t tk_load; // Previous tick to load picture
    bool displayed;   // To indicate if Bitmap(bmpId) is displayed
    BitmapId bmpId;
    void load_bmp(BitmapId &bmpId, const char *filename);
    void resize_show_img(ScalableImage &img_widget, BitmapId &bmpId);
};

#endif // SCREEN_DISPVIEW_HPP
