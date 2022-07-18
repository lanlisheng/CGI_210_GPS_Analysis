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
  float Speed_Data[4];
  Longtitude_And_Latitude_Data_Type Lat_Data;
  Longtitude_And_Latitude_Data_Type Long_Data;
} CGI_Data_Record_Frame_Type;

/* GPS Datas */
extern float AccRaw[3];
extern float GyoRaw[3];
extern float AngleRaw[3];
extern Longtitude_And_Latitude_Data_Type Longtitude_Data;
extern Longtitude_And_Latitude_Data_Type Latitude_Data;
extern double Altitude;
extern float SpeedValue[4];
extern uint8_t NSV[2];

extern uint8_t Data_Record_Frame_CNT;
extern CGI_Data_Record_Frame_Type CGI_Data_Record_Freme[10];

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