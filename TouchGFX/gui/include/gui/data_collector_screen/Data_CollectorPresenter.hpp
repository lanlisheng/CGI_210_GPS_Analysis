#ifndef DATA_COLLECTORPRESENTER_HPP
#define DATA_COLLECTORPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Data_CollectorView;

class Data_CollectorPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Data_CollectorPresenter(Data_CollectorView& v);

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

    virtual ~Data_CollectorPresenter() {};

private:
    Data_CollectorPresenter();

    Data_CollectorView& view;
};

#endif // DATA_COLLECTORPRESENTER_HPP
