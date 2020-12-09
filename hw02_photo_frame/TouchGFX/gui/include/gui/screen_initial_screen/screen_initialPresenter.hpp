#ifndef SCREEN_INITIALPRESENTER_HPP
#define SCREEN_INITIALPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_initialView;

class screen_initialPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_initialPresenter(screen_initialView& v);

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

    virtual ~screen_initialPresenter() {};

private:
    screen_initialPresenter();

    screen_initialView& view;
};

#endif // SCREEN_INITIALPRESENTER_HPP
