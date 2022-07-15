#ifndef DATA_COLLECTORVIEW_HPP
#define DATA_COLLECTORVIEW_HPP

#include <gui_generated/data_collector_screen/Data_CollectorViewBase.hpp>
#include <gui/data_collector_screen/Data_CollectorPresenter.hpp>

class Data_CollectorView : public Data_CollectorViewBase
{
public:
    Data_CollectorView();
    virtual ~Data_CollectorView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DATA_COLLECTORVIEW_HPP
