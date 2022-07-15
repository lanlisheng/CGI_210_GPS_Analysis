#include "cgi210.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include <stdio.h>

/* GPS Datas */
float AccRaw[3];
float GyoRaw[3];
float AngleRaw[3];
Longtitude_And_Latitude_Data_Type Longtitude_Data;
Longtitude_And_Latitude_Data_Type Latitude_Data;
double Altitude;
float SpeedValue[4];
uint8_t NSV[2];

/* Data records */
uint8_t Data_Record_Frame_CNT = 0;
CGI_Data_Record_Frame_Type CGI_Data_Record_Freme[10] = {{
    {0},
    {0},
    {0},
    {
        0,
        0,
        0.0,
        0x2D,
    },
    {
        0,
        0,
        0.0,
        0x2D,
    },
    {0},
    {0},
}};
//从buf里面得到第cx个逗号所在的位置
//返回值:0~0XFE,代表逗号所在位置的偏移.
//       0XFF,代表不存在第cx个逗号
uint8_t NMEA_Comma_Pos(uint8_t *GPS_Data, uint8_t cx) {
  uint8_t *p = GPS_Data;
  while (cx) {
    /* code */
    if (*GPS_Data == '*' || *GPS_Data < ' ' || *GPS_Data > 'z') {
      //遇到'*'或者非法字符，则不存在第cx个逗号
      return 0xFF;
    }
    if (*GPS_Data == ',') {
      cx--;
    }
    GPS_Data++;
  }
  return GPS_Data - p;
}

// m^n函数
//返回值:m^n次方.
uint32_t NMEA_Pow(uint8_t m, uint8_t n) {
  uint32_t result = 1;
  while (n--)
    result *= m;
  return result;
}

// str转换为数字,以','或者'*'结束
// buf:数字存储区
// dx:小数点位数,返回给调用函数
//返回值:转换后的数值
int NMEA_Str2num(uint8_t *buf, uint8_t *dx) {
  uint8_t *p = buf;
  uint32_t ires = 0, fres = 0;
  uint8_t ilen = 0, flen = 0;
  uint8_t mask = 0;
  int res;
  while (1) //得到整数和小数的长度
  {
    if (*p == '-') { //负数
      mask |= 0x02;
      p++;
    }

    if ((*p == ',') || (*p == '*')) { //结束
      break;
    }

    if (*p == '.') { //遇到小数点
      mask |= 0x01;
      p++;
    } else if ((*p > '9') || (*p < '0')) { //非法字符
      ilen = 0;
      flen = 0;
      break;
    }

    if (mask & 0x01) {
      flen++;
    } else {
      ilen++;
    }
    p++;
  }

  if (mask & 0x02) {
    buf++; //去掉负号
  }
  for (uint8_t i = 0; i < ilen; i++) //得到整数部分数据
  {
    ires += NMEA_Pow(10, ilen - 1 - i) * (buf[i] - '0');
  }

  if (flen > 5) {
    flen = 5; //最多取五位小数
  }
  *dx = flen; //得到小数点位数
  for (uint8_t i = 0; i < flen; i++) {
    //得到小数部分的数据
    fres += NMEA_Pow(10, flen - 1 - i) * (buf[ilen + 1 + i] - '0');
  }
  res = ires * NMEA_Pow(10, flen) + fres;
  if (mask & 0x02) {
    res = -res;
  }
  return res;
}

/* 华测CGI210组合惯导数据解析 */
void NMEA_GPCHC_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  int32_t temp = 0;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPCHC");

  posx = NMEA_Comma_Pos(p1, 3); //得到偏航角
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 4); //得到俯仰角
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 5); //得到横滚角
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AngleRaw[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 6); //得到陀螺X轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 7); //得到陀螺Y轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 8); //得到陀螺Z轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    GyoRaw[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 9); //得到加表X轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 10); //得到加表Y轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 11); //得到加表Z轴
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    AccRaw[2] = temp * 1.0 / NMEA_Pow(10, 2);
  }

  posx = NMEA_Comma_Pos(p1, 14); //得到高度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Altitude = temp / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 15); //得到东向速度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[0] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 16); //得到北向速度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[1] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 17); //得到天向速度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[2] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 18); //得到车辆速度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    SpeedValue[3] = temp * 1.0 / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 19); //得到主天线1的卫星数
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    NSV[0] = temp / NMEA_Pow(10, dx);
  }

  posx = NMEA_Comma_Pos(p1, 20); //得到副天线2的卫星数
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    NSV[1] = temp / NMEA_Pow(10, dx);
  }
}

/* 华测CGI210 通用数据解析 GPGGA */
void NMEA_GPGGA_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  uint32_t temp;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPGGA");
  posx = NMEA_Comma_Pos(p1, 2); //得到纬度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Latitude_Data.Degrees = temp / NMEA_Pow(10, dx + 2); //得到°
    Latitude_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //得到'
    Latitude_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 3); //得到南纬还是北纬
  if (posx != 0xFF) {
    Latitude_Data.Hemisphere = *(p1 + posx);
  }

  posx = NMEA_Comma_Pos(p1, 4); //得到经度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    Longtitude_Data.Degrees = temp / NMEA_Pow(10, dx + 2); //得到°
    Longtitude_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //得到’
    Longtitude_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 5); //得到东经还是西经
  if (posx != 0xFF) {
    Longtitude_Data.Hemisphere = *(p1 + posx);
  }
}

/* Add new frame record */
void Data_Record_Add_New_Frame(void) {
  CGI_Data_Record_Frame_Type Data_Frame;

  for (uint8_t i = 0; i < 3; i++) {
    Data_Frame.Angle_Data[i] = AngleRaw[i];
    Data_Frame.Gyro_Data[i] = GyoRaw[i];
    Data_Frame.Acc_Data[i] = AccRaw[i];
    Data_Frame.Speed_Data[i] = SpeedValue[i];
  }
  Data_Frame.Speed_Data[3] = SpeedValue[3];

  Data_Frame.NSV_Number[0] = NSV[0];
  Data_Frame.NSV_Number[1] = NSV[1];

  Data_Frame.Lat_Data = Latitude_Data;
  Data_Frame.Long_Data = Longtitude_Data;

  /* A simple FIFO algorithm */
  if (Data_Record_Frame_CNT <= 9) {
    CGI_Data_Record_Freme[Data_Record_Frame_CNT] = Data_Frame;
    Data_Record_Frame_CNT++;
  } else {
    for (uint8_t i = 0; i < 9; i++) {
      CGI_Data_Record_Freme[i] = CGI_Data_Record_Freme[i + 1];
    }
    CGI_Data_Record_Freme[9] = Data_Frame;
  }
}