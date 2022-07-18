#ifndef DATA_COLLECTORVIEW_HPP
#define DATA_COLLECTORVIEW_HPP

#include <gui/containers/DataCollect_Element.hpp>
#include <gui/data_collector_screen/Data_CollectorPresenter.hpp>
#include <gui_generated/data_collector_screen/Data_CollectorViewBase.hpp>

class Data_CollectorView : public Data_CollectorViewBase {
public:
  Data_CollectorView();
  virtual ~Data_CollectorView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();

  virtual void handleTickEvent();

protected:
  static const int numberOfListElements = 10;
  DataCollect_Element listElements[numberOfListElements];
};

#endif // DATA_COLLECTORVIEW_HPP
