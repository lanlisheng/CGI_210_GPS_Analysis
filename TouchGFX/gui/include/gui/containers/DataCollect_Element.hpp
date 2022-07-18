#ifndef DATACOLLECT_ELEMENT_HPP
#define DATACOLLECT_ELEMENT_HPP

#include "cgi210.h"
#include <gui_generated/containers/DataCollect_ElementBase.hpp>

class DataCollect_Element : public DataCollect_ElementBase {
public:
  DataCollect_Element();
  virtual ~DataCollect_Element() {}

  virtual void initialize();

  /**
   * Initialize this containers widgets
   */
  void Update_ListElement(int16_t List_Order, float *Acc_Data, float *Gyro_Data,
                          float *Angle_Data, float *Speed_Data,
                          Longtitude_And_Latitude_Data_Type Lat_Data,
                          Longtitude_And_Latitude_Data_Type Long_Data);

  void Init_ListElement(int16_t List_Order);

protected:
};

#endif // DATACOLLECT_ELEMENT_HPP
