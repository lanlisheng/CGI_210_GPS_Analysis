#include "cgi210.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include <stdio.h>

CGI_Data_Record_Frame_Type CGI_Data_Record_Freme;

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
  int32_t temp;
  float rs;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPCHC");

  posx = NMEA_Comma_Pos(p1, 3); //得到偏航角
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Heading_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Heading_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Heading_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 4); //得到俯仰角
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Pitch_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Pitch_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Pitch_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 5); //得到横滚角
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Roll_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Roll_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Roll_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 6); //得到陀螺X轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_X = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_X is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_X) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 7); //得到陀螺Y轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_Y = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_Y  is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_Y) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 8); //得到陀螺Z轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_Z = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_Z is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_Z) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 9); //得到加表X轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_X = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_X  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_X) / 10000);
  }

  posx = NMEA_Comma_Pos(p1, 10); //得到加表Y轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_Y = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_Y  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_Y) / 10000);
  }

  posx = NMEA_Comma_Pos(p1, 11); //得到加表Z轴
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_Z = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_Z  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_Z) / 10000);
  }

  //   posx = NMEA_Comma_Pos(p1, 12); //得到纬度
  //   if (posx != 0xFF) {
  //     CGI_Data_Record_Freme.Lat_Data.Degrees = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Minutes = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Seconds = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Hemisphere = NMEA_Str2num(p1 + posx,
  //     &dx);
  //   }

  //   posx = NMEA_Comma_Pos(p1, 13); //得到经度
  //   if (posx != 0xFF) {
  //     CGI_Data_Record_Freme.Long_Data.Degrees = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Minutes = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Seconds = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Hemisphere = NMEA_Str2num(p1 + posx,
  //     &dx);
  //   }

  posx = NMEA_Comma_Pos(p1, 14); //得到高度
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Altitude_Data = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 15); //得到东向速度
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.East_Speed = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 16); //得到北向速度
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.North_Speed = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 17); //得到天向速度
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.Celestial_Speed =
        NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 18); //得到车辆速度
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.Vehicle_Speed =
        NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 19); //得到主天线1的卫星数
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.NSV1_Number = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 20); //得到副天线2的卫星数
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.NSV2_Number = NMEA_Str2num(p1 + posx, &dx);
  }
}

/* 华测CGI210 通用数据解析 GPGGA */
void NMEA_GPGGA_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  uint32_t temp;
  float rs;
  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPGGA");
  posx = NMEA_Comma_Pos(p1, 2); //得到纬度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    CGI_Data_Record_Freme.Lat_Data.Degrees =
        temp / NMEA_Pow(10, dx + 2); //得到°
    CGI_Data_Record_Freme.Lat_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //得到'
    CGI_Data_Record_Freme.Lat_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;

    printf("\r\n");
    printf("CGI_Data_Record_Freme.Lat_Data.Degrees is %d\r\n",
           CGI_Data_Record_Freme.Lat_Data.Degrees);
    printf("CGI_Data_Record_Freme.Lat_Data.Minutes is %d\r\n",
           CGI_Data_Record_Freme.Lat_Data.Minutes);
    printf("CGI_Data_Record_Freme.Lat_Data.Seconds is %.2f\r\n",
           CGI_Data_Record_Freme.Lat_Data.Seconds);
  }

  posx = NMEA_Comma_Pos(p1, 3); //得到南纬还是北纬
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Lat_Data.Hemisphere = *(p1 + posx);
    printf("CGI_Data_Record_Freme.Lat_Data.Hemisphere is %c\r\n",
           CGI_Data_Record_Freme.Lat_Data.Hemisphere);
  }

  posx = NMEA_Comma_Pos(p1, 4); //得到经度
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    CGI_Data_Record_Freme.Long_Data.Degrees =
        temp / NMEA_Pow(10, dx + 2); //得到°
    CGI_Data_Record_Freme.Long_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //得到’
    CGI_Data_Record_Freme.Long_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 5); //得到东经还是西经
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Long_Data.Hemisphere = *(p1 + posx);
  }
}