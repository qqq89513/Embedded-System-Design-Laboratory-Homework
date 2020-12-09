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

    void load_bmp(BitmapId &bmpId, const char *filename);
    void resize_show_img(ScalableImage &img_widget, BitmapId &bmpId);

    Callback<screen_dispView, const Container &, const ClickEvent &> ClickCallback;

    static const uint8_t BMP_LIST_CNT = 5; // Picture counts
    BitmapId bmpId[BMP_LIST_CNT];
    const char *BMP_LIST[BMP_LIST_CNT] = {"logo_1.bmp", "logo_2.bmp", "ntust_1.bmp", "ntust_2.bmp", "ntust_3.bmp"}; // bmp file list
};

#endif // SCREEN_DISPVIEW_HPP
