#ifndef SCREEN_DISPPRESENTER_HPP
#define SCREEN_DISPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_dispView;

class screen_dispPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_dispPresenter(screen_dispView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_dispPresenter() {};

private:
    screen_dispPresenter();

    screen_dispView& view;
};

#endif // SCREEN_DISPPRESENTER_HPP
