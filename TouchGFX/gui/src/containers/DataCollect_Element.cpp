#include <gui/containers/DataCollect_Element.hpp>

DataCollect_Element::DataCollect_Element() {}

void DataCollect_Element::initialize() {
  DataCollect_ElementBase::initialize();
}

/**
 * Initialize this containers widgets
 */
void DataCollect_Element::Update_ListElement(
    int16_t List_Order, float *Acc_Data, float *Gyro_Data, float *Angle_Data,
    float *Speed_Data, Longtitude_And_Latitude_Data_Type Lat_Data,
    Longtitude_And_Latitude_Data_Type Long_Data) {
  if (List_Order < 10) {
    Unicode::snprintf(DataRecord_OrderBuffer, DATARECORD_ORDER_SIZE, "0%i",
                      List_Order);
    DataRecord_Order.invalidate();
    DataRecord_Order.resizeToCurrentTextWithAlignment();
  } else {
    Unicode::snprintf(DataRecord_OrderBuffer, DATARECORD_ORDER_SIZE, "%i",
                      List_Order);
    DataRecord_Order.invalidate();
    DataRecord_Order.resizeToCurrentTextWithAlignment();
  }

  /* Add New List Data */
  /* The acceleration*/
  Unicode::snprintfFloat(Acceleration_XBuffer, ACCELERATION_X_SIZE, "%.2f",
                         Acc_Data[0]);
  Acceleration_X.invalidate();
  Acceleration_X.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Acceleration_YBuffer, ACCELERATION_Y_SIZE, "%.2f",
                         Acc_Data[1]);
  Acceleration_Y.invalidate();
  Acceleration_Y.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Acceleration_ZBuffer, ACCELERATION_Z_SIZE, "%.2f",
                         Acc_Data[2]);
  Acceleration_Z.invalidate();
  Acceleration_Z.resizeToCurrentTextWithAlignment();

  /* The gyroscope */
  Unicode::snprintfFloat(Magnetic_XBuffer, MAGNETIC_X_SIZE, "%.2f",
                         Gyro_Data[0]);
  Magnetic_X.invalidate();
  Magnetic_X.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Magnetic_YBuffer, MAGNETIC_Y_SIZE, "%.2f",
                         Gyro_Data[1]);
  Magnetic_Y.invalidate();
  Magnetic_Y.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Magnetic_ZBuffer, MAGNETIC_Z_SIZE, "%.2f",
                         Gyro_Data[2]);
  Magnetic_Z.invalidate();
  Magnetic_Z.resizeToCurrentTextWithAlignment();

  /* The Angle */
  Unicode::snprintfFloat(Heading_AngleBuffer, HEADING_ANGLE_SIZE, "%.2f",
                         Angle_Data[0]);
  Heading_Angle.invalidate();
  Heading_Angle.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Pitch_AngleBuffer, PITCH_ANGLE_SIZE, "%.2f",
                         Angle_Data[1]);
  Pitch_Angle.invalidate();
  Pitch_Angle.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Roll_AngleBuffer, ROLL_ANGLE_SIZE, "%.2f",
                         Angle_Data[2]);
  Roll_Angle.invalidate();
  Roll_Angle.resizeToCurrentTextWithAlignment();

  Unicode::snprintf(Lattitude_MinutesBuffer1, LATTITUDE_MINUTESBUFFER1_SIZE,
                    "%i", Lat_Data.Degrees);
  Unicode::snprintf(Lattitude_MinutesBuffer2, LATTITUDE_MINUTESBUFFER2_SIZE,
                    "%i", Lat_Data.Minutes);
  Lattitude_Minutes.invalidate();
  Lattitude_Minutes.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Lattitude_SecondsBuffer1,
                         LATTITUDE_SECONDSBUFFER1_SIZE, "%2.2f",
                         Lat_Data.Seconds);
  Unicode::snprintf(Lattitude_SecondsBuffer2, LATTITUDE_SECONDSBUFFER2_SIZE,
                    "%c", Lat_Data.Hemisphere);
  Lattitude_Seconds.invalidate();
  Lattitude_Seconds.resizeToCurrentTextWithAlignment();
  Unicode::snprintf(Longtitude_MinutesBuffer1, LONGTITUDE_MINUTESBUFFER1_SIZE,
                    "%i", Long_Data.Degrees);
  Unicode::snprintf(Longtitude_MinutesBuffer2, LONGTITUDE_MINUTESBUFFER2_SIZE,
                    "%i", Long_Data.Minutes);
  Longtitude_Minutes.invalidate();
  Longtitude_Minutes.resizeToCurrentTextWithAlignment();
  Unicode::snprintfFloat(Longtitude_SecondsBuffer1,
                         LONGTITUDE_SECONDSBUFFER1_SIZE, "%2.2f",
                         Long_Data.Seconds);
  Unicode::snprintf(Longtitude_SecondsBuffer2, LONGTITUDE_SECONDSBUFFER2_SIZE,
                    "%c", Long_Data.Hemisphere);
  Longtitude_Seconds.invalidate();
  Longtitude_Seconds.resizeToCurrentTextWithAlignment();
}

/* Initialize List elements */
void DataCollect_Element::Init_ListElement(int16_t List_Order) {
  float Acc_Data[3] = {0.0};
  float Gyo_Data[3] = {0.0};
  float Angle_Data[3] = {0.0};
  float Speed_Data[4] = {0.0};
  Longtitude_And_Latitude_Data_Type Lat_Data, Long_Data;

  Lat_Data.Degrees = 0;
  Lat_Data.Minutes = 0;
  Lat_Data.Seconds = 0.0;
  Lat_Data.Hemisphere = 0x2D;
  Long_Data.Degrees = 0;
  Long_Data.Minutes = 0;
  Long_Data.Seconds = 0.0;
  Long_Data.Hemisphere = 0x2D;

  Update_ListElement(List_Order, Acc_Data, Gyo_Data, Angle_Data, Speed_Data,
                     Lat_Data, Long_Data);
}