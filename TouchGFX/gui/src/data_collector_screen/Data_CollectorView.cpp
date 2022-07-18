#include "cgi210.h"
#include <gui/data_collector_screen/Data_CollectorView.hpp>

Data_CollectorView::Data_CollectorView() {}

void Data_CollectorView::setupScreen() {
  Data_CollectorViewBase::setupScreen();

  for (uint8_t i = 0; i < numberOfListElements; i++) {
    listElements[i].Update_ListElement(
        i + 1, CGI_Data_Record_Freme[i].Acc_Data,
        CGI_Data_Record_Freme[i].Gyro_Data, CGI_Data_Record_Freme[i].Angle_Data,
        CGI_Data_Record_Freme[i].Speed_Data, CGI_Data_Record_Freme[i].Lat_Data,
        CGI_Data_Record_Freme[i].Long_Data);
    DataList.add(listElements[i]);
  }
}

void Data_CollectorView::tearDownScreen() {
  Data_CollectorViewBase::tearDownScreen();
}

void Data_CollectorView::handleTickEvent() {
  // Execute_DataRecordButton_Event();

  for (uint8_t i = 0; i < numberOfListElements; i++) {
    listElements[i].Update_ListElement(
        i + 1, CGI_Data_Record_Freme[i].Acc_Data,
        CGI_Data_Record_Freme[i].Gyro_Data, CGI_Data_Record_Freme[i].Angle_Data,
        CGI_Data_Record_Freme[i].Speed_Data, CGI_Data_Record_Freme[i].Lat_Data,
        CGI_Data_Record_Freme[i].Long_Data);
  }
  Data_CollectorView::handleKeyEvent(0);
}