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

typedef struct {
  double Gyro_X;
  double Gyro_Y;
  double Gyro_Z;
} Gyro_Data_TypeDef;

typedef struct {
  float acc_X;
  float acc_Y;
  float acc_Z;
} Acc_Data_TypeDef;

typedef struct {
  float East_Speed;
  float North_Speed;
  float Celestial_Speed;
  float Vehicle_Speed;
} Speed_Data_TypeDef;

/* 华测CGI210组合惯导数据解析 存储结构体 */
typedef struct {
  float Heading_Angle;
  float Pitch_Angle;
  float Roll_Angle;
  Gyro_Data_TypeDef Gyro_Data;
  Acc_Data_TypeDef Acc_Data;
  Longtitude_And_Latitude_Data_Type Lat_Data;
  Longtitude_And_Latitude_Data_Type Long_Data;
  double Altitude_Data;
  Speed_Data_TypeDef Speed_Data;
  uint8_t NSV1_Number;
  uint8_t NSV2_Number;
} CGI_Data_Record_Frame_Type;

void NMEA_GPCHC_Analysis(uint8_t *GPS_Data);
int NMEA_Str2num(uint8_t *buf, uint8_t *dx);
uint32_t NMEA_Pow(uint8_t m, uint8_t n);
uint8_t NMEA_Comma_Pos(uint8_t *buf, uint8_t cx);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CGI210_H_ */