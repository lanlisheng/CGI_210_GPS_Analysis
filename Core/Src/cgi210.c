#include "cgi210.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include <stdio.h>

CGI_Data_Record_Frame_Type CGI_Data_Record_Freme;

//��buf����õ���cx���������ڵ�λ��
//����ֵ:0~0XFE,����������λ�õ�ƫ��.
//       0XFF,�������ڵ�cx������
uint8_t NMEA_Comma_Pos(uint8_t *GPS_Data, uint8_t cx) {
  uint8_t *p = GPS_Data;
  while (cx) {
    /* code */
    if (*GPS_Data == '*' || *GPS_Data < ' ' || *GPS_Data > 'z') {
      //����'*'���߷Ƿ��ַ����򲻴��ڵ�cx������
      return 0xFF;
    }
    if (*GPS_Data == ',') {
      cx--;
    }
    GPS_Data++;
  }
  return GPS_Data - p;
}

// m^n����
//����ֵ:m^n�η�.
uint32_t NMEA_Pow(uint8_t m, uint8_t n) {
  uint32_t result = 1;
  while (n--)
    result *= m;
  return result;
}

// strת��Ϊ����,��','����'*'����
// buf:���ִ洢��
// dx:С����λ��,���ظ����ú���
//����ֵ:ת�������ֵ
int NMEA_Str2num(uint8_t *buf, uint8_t *dx) {
  uint8_t *p = buf;
  uint32_t ires = 0, fres = 0;
  uint8_t ilen = 0, flen = 0;
  uint8_t mask = 0;
  int res;
  while (1) //�õ�������С���ĳ���
  {
    if (*p == '-') { //����
      mask |= 0x02;
      p++;
    }

    if ((*p == ',') || (*p == '*')) { //����
      break;
    }

    if (*p == '.') { //����С����
      mask |= 0x01;
      p++;
    } else if ((*p > '9') || (*p < '0')) { //�Ƿ��ַ�
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
    buf++; //ȥ������
  }
  for (uint8_t i = 0; i < ilen; i++) //�õ�������������
  {
    ires += NMEA_Pow(10, ilen - 1 - i) * (buf[i] - '0');
  }

  if (flen > 5) {
    flen = 5; //���ȡ��λС��
  }
  *dx = flen; //�õ�С����λ��
  for (uint8_t i = 0; i < flen; i++) {
    //�õ�С�����ֵ�����
    fres += NMEA_Pow(10, flen - 1 - i) * (buf[ilen + 1 + i] - '0');
  }
  res = ires * NMEA_Pow(10, flen) + fres;
  if (mask & 0x02) {
    res = -res;
  }
  return res;
}

/* ����CGI210��Ϲߵ����ݽ��� */
void NMEA_GPCHC_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  int32_t temp;
  float rs;

  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPCHC");

  posx = NMEA_Comma_Pos(p1, 3); //�õ�ƫ����
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Heading_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Heading_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Heading_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 4); //�õ�������
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Pitch_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Pitch_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Pitch_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 5); //�õ������
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Roll_Angle = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Roll_Angle is %.2f\r\n",
           (CGI_Data_Record_Freme.Roll_Angle) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 6); //�õ�����X��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_X = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_X is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_X) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 7); //�õ�����Y��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_Y = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_Y  is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_Y) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 8); //�õ�����Z��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Gyro_Data.Gyro_Z = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Gyro_Data.Gyro_Z is %.2f\r\n",
           (CGI_Data_Record_Freme.Gyro_Data.Gyro_Z) / 100);
  }

  posx = NMEA_Comma_Pos(p1, 9); //�õ��ӱ�X��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_X = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_X  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_X) / 10000);
  }

  posx = NMEA_Comma_Pos(p1, 10); //�õ��ӱ�Y��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_Y = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_Y  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_Y) / 10000);
  }

  posx = NMEA_Comma_Pos(p1, 11); //�õ��ӱ�Z��
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Acc_Data.acc_Z = NMEA_Str2num(p1 + posx, &dx);
    printf("CGI_Data_Record_Freme.Acc_Data.acc_Z  is %.2f\r\n",
           (CGI_Data_Record_Freme.Acc_Data.acc_Z) / 10000);
  }

  //   posx = NMEA_Comma_Pos(p1, 12); //�õ�γ��
  //   if (posx != 0xFF) {
  //     CGI_Data_Record_Freme.Lat_Data.Degrees = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Minutes = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Seconds = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Lat_Data.Hemisphere = NMEA_Str2num(p1 + posx,
  //     &dx);
  //   }

  //   posx = NMEA_Comma_Pos(p1, 13); //�õ�����
  //   if (posx != 0xFF) {
  //     CGI_Data_Record_Freme.Long_Data.Degrees = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Minutes = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Seconds = NMEA_Str2num(p1 + posx, &dx);
  //     CGI_Data_Record_Freme.Long_Data.Hemisphere = NMEA_Str2num(p1 + posx,
  //     &dx);
  //   }

  posx = NMEA_Comma_Pos(p1, 14); //�õ��߶�
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Altitude_Data = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 15); //�õ������ٶ�
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.East_Speed = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 16); //�õ������ٶ�
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.North_Speed = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 17); //�õ������ٶ�
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.Celestial_Speed =
        NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 18); //�õ������ٶ�
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Speed_Data.Vehicle_Speed =
        NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 19); //�õ�������1��������
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.NSV1_Number = NMEA_Str2num(p1 + posx, &dx);
  }

  posx = NMEA_Comma_Pos(p1, 20); //�õ�������2��������
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.NSV2_Number = NMEA_Str2num(p1 + posx, &dx);
  }
}

/* ����CGI210 ͨ�����ݽ��� GPGGA */
void NMEA_GPGGA_Analysis(uint8_t *GPS_Data) {
  uint8_t *p1, dx;
  uint8_t posx;
  uint32_t temp;
  float rs;
  p1 = (uint8_t *)strstr((const char *)GPS_Data, "$GPGGA");
  posx = NMEA_Comma_Pos(p1, 2); //�õ�γ��
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    CGI_Data_Record_Freme.Lat_Data.Degrees =
        temp / NMEA_Pow(10, dx + 2); //�õ���
    CGI_Data_Record_Freme.Lat_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //�õ�'
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

  posx = NMEA_Comma_Pos(p1, 3); //�õ���γ���Ǳ�γ
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Lat_Data.Hemisphere = *(p1 + posx);
    printf("CGI_Data_Record_Freme.Lat_Data.Hemisphere is %c\r\n",
           CGI_Data_Record_Freme.Lat_Data.Hemisphere);
  }

  posx = NMEA_Comma_Pos(p1, 4); //�õ�����
  if (posx != 0xFF) {
    temp = NMEA_Str2num(p1 + posx, &dx);
    CGI_Data_Record_Freme.Long_Data.Degrees =
        temp / NMEA_Pow(10, dx + 2); //�õ���
    CGI_Data_Record_Freme.Long_Data.Minutes =
        ((temp % NMEA_Pow(10, dx + 2)) / NMEA_Pow(10, dx)); //�õ���
    CGI_Data_Record_Freme.Long_Data.Seconds =
        ((temp % NMEA_Pow(10, dx)) * (1.0) / NMEA_Pow(10, dx)) * 60.0;
  }

  posx = NMEA_Comma_Pos(p1, 5); //�õ�������������
  if (posx != 0xFF) {
    CGI_Data_Record_Freme.Long_Data.Hemisphere = *(p1 + posx);
  }
}