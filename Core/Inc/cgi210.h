#ifndef __CGI210_H_
#define __CGI210_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
  float Seconds;
  uint8_t Degrees;
  uint8_t Minutes;
  uint8_t Hemisphere;
} Longtitude_And_Latitude_Data_Type;

/* 华测CGI210组合惯导数据解析 存储结构体 */
typedef struct {
  float Angle_Data[3];
  float Gyro_Data[3];
  float Acc_Data[3];
  Longtitude_And_Latitude_Data_Type Lat_Data;
  Longtitude_And_Latitude_Data_Type Long_Data;
  float Speed_Data[4];
  uint8_t NSV_Number[2];
} CGI_Data_Record_Frame_Type;

void NMEA_GPCHC_Analysis(uint8_t *GPS_Data);
void NMEA_GPGGA_Analysis(uint8_t *GPS_Data);
int NMEA_Str2num(uint8_t *buf, uint8_t *dx);
uint32_t NMEA_Pow(uint8_t m, uint8_t n);
uint8_t NMEA_Comma_Pos(uint8_t *buf, uint8_t cx);

void Data_Record_Add_New_Frame(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CGI210_H_ */